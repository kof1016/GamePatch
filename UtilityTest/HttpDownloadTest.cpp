#include "pch.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Utility/ReceiverFacade.h"
#include "../Utility/IDownloadable.h"
#include "../Utility/FileTool.h"
#include "../Utility/DownloadProvider.h"

class FakeDonwload : public Utility::IDownloadable
{
public:
	FakeDonwload(int file_size) : _FileSize(file_size)
	{
	}

	FakeDonwload(int file_size, int downloaded) : _FileSize(file_size), _DownloadedSize(downloaded)
	{
	}

	virtual ~FakeDonwload()
	{
	}

	std::shared_ptr<Utility::ReceiverFacade> Start(std::string url) override
	{
		return _ReceiverFacade;
	}


	void ReceiveData(char* data, int total)
	{
		_DownloadedSize += total;
		if (_DownloadedSize >= _FileSize)
		{
			_ReceiverFacade->InvokeDownloadDone(true);
		}

		_ReceiverFacade->InvokeWriteData(data, total);
		_ReceiverFacade->InvokeProgress(_FileSize, _DownloadedSize);
	}

private:
	std::shared_ptr<Utility::ReceiverFacade> _ReceiverFacade{new Utility::ReceiverFacade()};
	int _FileSize{0};
	int _DownloadedSize{0};
};

SCENARIO("fake download", "[httpdownload]")
{
	//arrange
	std::vector<char> file(1, 0);

	FakeDonwload download(file.size()); //user

	//act
	auto facade = download.Start("");

	facade->BindWriteData
	(
		[&](char* buffer, size_t total)
		{
		}
	);

	facade->BindProgress
	(
		[=](int total, int downloaded)
		{
			const auto percent = downloaded * 100.0 / total;
			std::cout << "fake percent=" << percent << "%" << "\r";
		}
	);

	bool done = false;
	facade->BindReceiverDone
	(
		[&](bool result)
		{
			done = result;
		}
	);

	download.ReceiveData(file.data(), 1);

	//assert
	REQUIRE(done == true);
}


/*
Feature: resume download
in order to 節省更新時間
as s 玩家
i want to be 可以續傳
*/
SCENARIO("fake download break", "[httpdownload]")
{
	GIVEN("i start download")
	{
		std::vector<char> sourceFile;
		std::vector<char> localFile;
		bool done = false;
		WHEN("i get remote file size")
		{
			sourceFile = {'1', '2', '3', '4', '5'};
			FakeDonwload download(sourceFile.size());
			auto facade = download.Start("");

			AND_WHEN("write data to local file")
			{
				facade->BindWriteData
				(
					[&](char* buffer, size_t total)
					{
						localFile.assign(buffer, buffer + total);
					}
				);

				facade->BindProgress
				(
					[=](int total, int downloaded)-> int
					{
						const auto percent = downloaded * 100.0 / total;
						std::cout << "fake percent=" << percent << "%" << "\r";
						return 0;
					}
				);

				facade->BindReceiverDone
				(
					[&](bool result)
					{
						done = result;
					}
				);

				AND_WHEN("i stop download")
				{
					download.ReceiveData(sourceFile.data(), 1);

					REQUIRE_FALSE(done);

					THEN("i get unfinish file size")
					{
						REQUIRE(localFile.size() == 1);
						REQUIRE(localFile.at(0) == '1');

						AND_THEN("i get leftover size")
						{
							int leftover = sourceFile.size() - localFile.size();
							REQUIRE(leftover == 4);
						}
					}
				}
			}
		}
	}
}

SCENARIO("fake resume download", "[httpdownload]")
{
	GIVEN("i restart download")
	{
		std::vector<char> source = {'1', '2', '3', '4', '5'};
		std::vector<char> target = {'1'};
		std::vector<char> leftover = {'2', '3', '4', '5'};
		bool done = false;

		WHEN("i open local unifish file")
		{
			AND_WHEN("i start here keep on download to file end")
			{
				FakeDonwload download(source.size(), target.size());
				auto facade = download.Start("");

				facade->BindWriteData
				(
					[&](char* buffer, size_t total)
					{
						target.insert(target.end(), buffer, buffer + total);
					}
				);

				facade->BindProgress
				(
					[=](int total, int downloaded)
					{
						const auto percent = downloaded * 100.0 / total;
						std::cout << "fake percent=" << percent << "%" << "\r";
					}
				);

				facade->BindReceiverDone
				(
					[&](bool result)
					{
						done = result;
					}
				);

				THEN("i get complete file")
				{
					download.ReceiveData(leftover.data(), 4);

					REQUIRE(target.size() == source.size());

					REQUIRE(done);
				}
			}
		}
	}
}


TEST_CASE("download one file", "[httpdownload]")
{
	//arrange
	std::string url = "http://tpdb.speed2.hinet.net/test_040m.zip";

	//std::string url = "https://dl.google.com/dl/android/studio/install/3.0.1.0/android-studio-ide-171.4443003-windows.exe";
	std::string filename = "testfile1.txt";
	FILE* fp = std::fopen(filename.c_str(), "w");

	//act
	Utility::DownloadProvider download; //user
	auto size = FileTool::GetFileSize_C(filename);
	auto size1 = FileTool::GetFileSize_CPlusPlus(filename);

	auto facade = download.Start(url);

	facade->BindWriteData
	(
		[&](char* buffer, size_t nmemb)
		{
			fwrite(buffer, 1, nmemb, fp);
		}
	);

	facade->BindProgress
	(
		[=](int total, int downloaded)
		{
			const auto percent = downloaded * 100.0 / total;
			std::cout << "percent=" << percent << "\r";
		}
	);

	bool done = false;
	facade->BindReceiverDone
	(
		[&](bool result)
		{
			fclose(fp);
			done = result;
		}
	);

	while (!done) //main loop
	{
	}

	//assert
	REQUIRE(done == true);
}

SCENARIO("download muti file", "[httpdownload]")
{
	GIVEN("i have url list")
	{
		std::vector<std::tuple<std::string, std::string>> urls;

		urls.emplace_back("http://tpdb.speed2.hinet.net/test_040m.zip", "file0.txt");
		urls.emplace_back("http://tpdb.speed2.hinet.net/test_040m.zip", "file1.txt");

		WHEN("i ready download")
		{
			Utility::DownloadProvider download; //user

			THEN("i receive file in disk")
			{
				for (auto&& tuple : urls)
				{
					const auto url = std::get<0>(tuple);
					auto filename = std::get<1>(tuple);

					auto receiver = download.Start(url);

					auto fp = fopen(filename.c_str(), "w");

					receiver->BindWriteData
					(
						[&](char* buffer, size_t nmemb)
						{
							fwrite(buffer, 1, nmemb, fp);
						}
					);

					receiver->BindProgress
					(
						[=](int total, int downloaded)
						{
							const auto percent = downloaded * 100.0 / total;
							std::cout << "percent=" << percent << "%" << "\r";
						}
					);


					bool done = false;
					receiver->BindReceiverDone
					(
						[&](bool result)
						{
							fclose(fp);
							done = result;
							//std::cout << std::endl;
						}
					);

					while (!done)
					{
					}

					REQUIRE(done == true);
				}
			}
		}
	}
}

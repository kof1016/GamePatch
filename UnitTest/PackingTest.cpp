#include "pch.h"

#include "catch.hpp"
#include "../Utility/FileTool.h"
#include <filesystem>
#include "../PackingLogic/ScanResourceFolder.h"
#include "../PackingLogic/GetFileList.h"
#include "../PackingLogic/DataDefine.h"
#include "../Utility/FileWriter.h"
#include "../PackingLogic/CreateFileListToFile.h"
#include "../Utility/cpplinq.hpp"


TEST_CASE("get FileList test", "[packing]")
{
	//auto path = PackingLogic::GetCurrentFileListPath(1);

	auto path = "filelist_empty.txt";
	PackingLogic::GetFileList getFileList(path);
	auto fileList = getFileList.Result();
	REQUIRE(fileList.Version == 0);
}

TEST_CASE("ScanResourceFolder test", "[packing]")
{
	const auto path = PackingLogic::GetResourcePath();

	PackingLogic::ScanResourceFolder maker(path);

	const auto r = maker.Make();

	REQUIRE(r.Contents.size() ==3);
}

TEST_CASE("update ver test", "[packing]")
{
	const auto path = PackingLogic::GetNewestVerPath();
	PackingLogic::GetFileList getCurrentVer(path);
	const auto data = getCurrentVer.Result();
	const auto newestVer = data.Version + 1;

	Utility::FileWriter writer(path);
	writer.OpenFile();

	const auto write = "ver=" + std::to_string(newestVer);
	writer.Write(write.data(), write.size());

	writer.CloseFile();

	REQUIRE(newestVer == data.Version+1);
}

TEST_CASE("save filelist test", "[packing]")
{
	//arrange
	int newestVer = 1;
	std::list<Utility::FileList::Content> files
	{
		{"+", "1", "path1"},
		{"+", "2", "path2"},
		{"+", "3", "path3"},
		{"+", "4", "path4"},
		{"+", "5", "path5"},
	};

	auto path = PackingLogic::GetCurrentFileListPath(newestVer);

	namespace fs = std::experimental::filesystem;
	fs::path p(path);
	if (!exists(p.parent_path()))
	{
		create_directories(p.parent_path());
	}

	std::ofstream outfile(path, std::ofstream::out); //write mode

	for (auto& c : files)
	{
		outfile << c.StateSymbol << "|" << c.MD5 << "|" << c.Path << std::endl;
	}

	outfile.close();
}

TEST_CASE("Create zip test", "[packing]")
{
	//arrange
	std::list<Utility::FileList::Content> _FileList
	{
		{"+", "1", "1.txt"},
		{"+", "2", "2.txt"},
		{"+", "3", "3.txt"},
		{"+", "4", "path4"},
		{"+", "5", "path5"},
	};


	namespace fs = std::experimental::filesystem;

	auto fromPath = PackingLogic::GetResourcePath();

	fs::path toPath(PackingLogic::GetCurrentFileListPath(1));


	for (auto& p : fs::directory_iterator(fromPath))
	{
		const auto r = std::find_if(_FileList.begin(), _FileList.end(),
									[&](Utility::FileList::Content& d)
									{
										auto name = p.path().filename();
										return name == d.Path;
									});

		if (r != _FileList.end())
		{
			copy_file(p.path(), toPath.parent_path() / p.path().filename());
		}
	}
}

TEST_CASE("copy file", "[packing]")
{
	//arrange
	namespace fs = std::experimental::filesystem;

	auto fromPath = PackingLogic::GetResourcePath();

	fs::path toPath(PackingLogic::GetCurrentFileListPath(1));


	for (auto& p : fs::directory_iterator(fromPath))
	{
		auto& fp = p.path();
		copy_file(p.path(), toPath.parent_path() / fp.filename());
	}
}

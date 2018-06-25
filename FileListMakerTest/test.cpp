#include "pch.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../FileListMaker/FileListCreator.h"
#include "../Utility/IParser.h"
#include "../Utility/FileListParser.h"
#include "../Utility/FileTool.h"
#include <filesystem>


class Step3
{
public:
	Step3(int i)
	{
		money = i;
	}

	int Return()
	{
		return 3;
	}

	int money;
};

class Step2
{
public:
	Step2(int i)
	{
		money = i;
	}

	int Return()
	{
		return 2;
	}

	int money;
};

class Step1
{
public:
	Step1()
	{
	};

	int Return()
	{
		return 1;
	}
};

TEST_CASE("filelistmaker test", "[filelistmaker]")
{
	auto step1 = Step1();
	auto step2 = Step2(step1.Return());
	auto step3 = Step3(step2.Return());
	REQUIRE(step3.Return() == 3);
}

TEST_CASE("get newest ver filelist", "[filelistmaker]")
{
	//arrange
	namespace fs = std::experimental::filesystem;
	const auto path = fs::current_path();
	auto filePath = path / "resource_pack" / "ver.txt";

	//act
	FileListMaker::FileListCreator fileListReader;
	auto data = fileListReader.Create(filePath.string());

	//assert
	REQUIRE(data.Version == 0);
}

TEST_CASE("first packing", "[filelistmaker]")
{
	//arrange
	const std::string write{"ver=1"};

	const std::string write2 =  "ver=" + std::to_string(1) ;
	

	//act
	std::ofstream outfile("NewestVer.txt", std::ofstream::out); //write mode | write data from eof 

	outfile << write;
	outfile.close();

	//assert
	std::ifstream infile("NewestVer.txt", std::ios::in); //read mode | read to end

	if (!infile.is_open())
	{
		int i = 0;
		assert("open file error, testfile.txt");
		return;
	}

	 std::string read;
	// while (infile >> read)
	// {
	// 	std::cout << read;
	// 	if (infile.peek() == '\n') //detect "\n"
	// 	{
	// 		std::cout << std::endl;
	// 	}
	// }
	// infile.close();
	
	infile >> read;
	infile.close();

	REQUIRE(write == read);
}

TEST_CASE("scan resource folder test", "[filelistmaker]")
{
	//arrange
	namespace fs = std::experimental::filesystem;
	const auto path = fs::current_path();
	auto filePath = path / "resource";

	//act
	FileListMaker::FileListCreator fileListReader;
	auto data = fileListReader.Create(filePath.string());

	//assert
	REQUIRE(data.Version == 0);
}

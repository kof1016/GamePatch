#include "pch.h"
#include "catch.hpp"
#include "../Utility/md5.h"
#include <fstream>
#include <experimental/filesystem>
#include <unordered_map>
#include "../Utility/FileListParser.h"
#include "../PackingLogic/PackingLogic.h"

TEST_CASE("Filesystem test", "[file]")
{
	std::string ver = "1";
	namespace fs = std::experimental::filesystem;
	fs::create_directories("resource_pack/ver" + ver);

	fs::create_directories("sandbox/1/2/a");
	fs::create_directory("sandbox/1/2/b");

	fs::create_directory("sandbox/1/2/c", "sandbox/1/2/b");

	std::experimental::filesystem::path p1("c:\\windows");
	std::experimental::filesystem::path p2 = p1 / "system32";
}

TEST_CASE("FileList Parser Test", "[file]")
{
	//arrange
	const std::string data =
		"ver=1"
		"+|9e107d9d372bb6826bd81d3542a419d6|actions/1.png";
	//act
	Utility::FileListParser parser;

	auto filelist = parser.Parser(data);

	// assert
	REQUIRE(filelist.Version == 1);
	REQUIRE(filelist.Contents[0].State == DataDefine::FileList::Content::ADD);
	REQUIRE(filelist.Contents[0].MD5== "9e107d9d372bb6826bd81d3542a419d6");
	REQUIRE(filelist.Contents[0].Path == "actions/1.png");
}

TEST_CASE("first config parser", "[file]")
{
	//arrange
	const std::string data;

	//act
	Utility::FileListParser parser;
	auto filelist = parser.Parser(data);

	// assert
	REQUIRE(filelist.Version == 0);
	REQUIRE(filelist.Contents.empty());
}

TEST_CASE("File IO C Style", "[file]")
{
	std::FILE* fp = std::fopen("dummy.txt", "w");
	assert(fp);

	std::fseek(fp, 0, SEEK_END); // seek to end
	const std::size_t filesize = std::ftell(fp);

	std::fseek(fp, 0, SEEK_SET); // seek to start
	std::vector<uint8_t> buffer(filesize);

	std::fread(buffer.data(), sizeof(uint8_t), buffer.size(), fp);

	MD5 md5;
	md5.update(buffer.data(), buffer.size());
	md5.finalize();

	const auto strMd5 = md5.hexdigest();

	std::fclose(fp);
	std::printf("i've read %zi bytes\n", filesize);

	std::string a = "327c478cce88005e6ad0d5ad10811b11";

	a.compare(strMd5);

	std::cout << strMd5 << std::endl;
}

TEST_CASE("File IO C++ Style", "[file]")
{
	std::ifstream infile(R"(..\resources\1.txt)", std::ios::in | std::ios::ate); //read mode | read to end

	if (!infile.is_open())
	{
		int i = 0;
		assert("open file error, testfile.txt");
		return;
	}

	const auto size = infile.tellg();

	std::vector<unsigned char> buffer(size);

	infile.seekg(0);
	infile.read(reinterpret_cast<char*>(buffer.data()), size);
	infile.close();

	std::ofstream outfile("md5list.txt", std::ofstream::out | std::ofstream::app); //write mode | write data from eof 

	outfile << buffer.data() << std::endl;

	outfile.close();
}

TEST_CASE("MD5 Test", "[file]")
{
	std::vector<uint8_t> buffer{123};
	std::vector<uint8_t> buffer2{123};

	MD5 md5;
	md5.update(buffer.data(), buffer.size());
	md5.finalize();
	const auto result = md5.hexdigest();

	md5.update(buffer2.data(), buffer2.size());
	md5.finalize();
	const auto result2 = md5.hexdigest();

	REQUIRE(result == result2);
}

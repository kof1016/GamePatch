#include "pch.h"
#include "catch.hpp"
#include "../Utility/md5.h"
#include <fstream>
#include <experimental/filesystem>
#include <unordered_map>
#include "../Utility/DataParser.h"
#include "../Utility/FileWriter.h"

TEST_CASE("Filesystem test", "[file]")
{
	auto p = Utility::PACKING_FOLDER_NAME / Utility::NEWESTVER_NAME;
	std::vector<char> buffer{ '1','\0'};

	FILE* file = std::fopen(p.string().data(), "w");
	fwrite(buffer.data(), 1, buffer.size(), file);
	fclose(file);
}


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
	const std::string data_ver = "ver=1";

	const std::string data_filelist ="+|9e107d9d372bb6826bd81d3542a419d6|actions/1.png";
	//act
	Utility::DataParser parser;


	auto verNum = Utility::DataParser::ParserVersionNumber(data_ver);

	auto filelist = Utility::DataParser::ParserFileList(data_filelist);

	// assert
	REQUIRE(verNum == 1);
	
	REQUIRE(filelist.front().StateSymbol == "+");
	REQUIRE(filelist.front().MD5== "9e107d9d372bb6826bd81d3542a419d6");
	REQUIRE(filelist.front().Path == "actions/1.png");
}

TEST_CASE("first config parser", "[file]")
{
	//act
	auto verNum = Utility::DataParser::ParserVersionNumber("");
	auto filelist = Utility::DataParser::ParserFileList("");

	// assert
	REQUIRE(verNum == 0);
	REQUIRE(filelist.empty());
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

#include "pch.h"
#include "catch.hpp"
#include <fstream>

#include <cassert>
#include "../Utility/md5.h"
#include "../Utility/DataParser.h"
#include "../curl/curl.h"
#include "../Utility/CurlHttp.h"
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include <iostream>
#include <tchar.h>
#include "../PackingLogic/ScanResourceFolder.h"
#include "../Utility/FileTool.h"

using namespace std;

TEST_CASE("Filesystem remove test", "[file]")
{
	auto n = remove_all("sandbox");
	std::cout << "Deleted " << n << " files or directories\n";
}


TEST_CASE("Filesystem test", "[file]")
{
	std::string ver = "1";
	
	create_directories("resource_pack/ver" + ver);
	create_directories("sandbox/1/2/a");
	create_directory("sandbox/1/2/b");

	create_directory("sandbox/1/2/c", "sandbox/1/2/b");

	path p1("c:\\windows");
	path p2 = p1 / "system32";
}

TEST_CASE("FileList Parser Test", "[file]")
{
	//arrange
	const std::string data_ver = "ver=1";

	const std::string data_filelist = "+|9e107d9d372bb6826bd81d3542a419d6|actions/1.png";
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

TEST_CASE("FileList Parser by file Test", "[file]")
{
	//arrange
	path filePath = Utility::PACKING_FOLDER_NAME / Utility::NEWESTVER_NAME;

	//act
	Utility::DataParser parser;

	auto verNum = Utility::DataParser::ParserVersionNumberByFile(filePath.string());

	//auto filelist = Utility::DataParser::ParserFileList(data_filelist);

	// assert
	REQUIRE(verNum == 1);

	// REQUIRE(filelist.front().StateSymbol == "+");
	// REQUIRE(filelist.front().MD5 == "9e107d9d372bb6826bd81d3542a419d6");
	// REQUIRE(filelist.front().Path == "actions/1.png");
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

// int writeInZipFile(zipFile zFile, const std::string& file)
// {
// 	std::fstream f(file.c_str(), std::ios::binary | std::ios::in);
// 	f.seekg(0, std::ios::end);
// 	const long size = f.tellg();
// 	f.seekg(0, std::ios::beg);
// 	if (size <= 0)
// 	{
// 		return zipWriteInFileInZip(zFile, nullptr, 0);
// 	}
// 	vector<char> buf;
// 	buf.resize(size);
// 	f.read(buf.data(), size);
// 	int ret = zipWriteInFileInZip(zFile, buf.data(), size);
// 	return ret;
// }



 TEST_CASE("minizip-zip test", "[file]")
 {
 	const auto fileList = PackingLogic::ScanResourceFolder("TestFolder").Make();

 	const auto zFile = zipOpen("testpack2.zip", APPEND_STATUS_CREATE);
 	
 	for(auto& p : fileList)
 	{
 		zip_fileinfo zFileInfo;

 		int ret = zipOpenNewFileInZip(zFile, p.Path.data(), &zFileInfo, nullptr, 0, nullptr, 0, nullptr, 0, Z_DEFAULT_COMPRESSION);
 		if (ret != ZIP_OK)
 		{
 			cout << "openfile in zip failed" << endl;
 			zipClose(zFile, nullptr);
 			return;
 		}
 		vector<char> buffer;
 		FileTool::ReadFileToBufferToBinary(p.Path, buffer);
 		ret = zipWriteInFileInZip(zFile, buffer.data(), buffer.size());
 		
 		if (ret != ZIP_OK)
 		{
 			cout << "write in zip failed" << endl;
 			zipClose(zFile, nullptr);
 			return;
 		}
 	}
 	
 	zipClose(zFile, nullptr);
 	cout << "zip ok" << endl;
 }

 TEST_CASE("minizip-unzip", "[file]")
 {
 #define READ_SIZE 8192  
 #define MAX_FILENAME 512  

 	// Open the zip file  
 	const auto zipfile = unzOpen("testpack2.zip");
 	if (zipfile == nullptr)
 	{
 		std::cout << "not found\n";
 		return;
 	}

 	// Get info about the zip file  
 	unz_global_info global_info;
 	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
 	{
 		std::cout << "could not read file global info\n";
 		unzClose(zipfile);
 		return;
 	}

 	// Buffer to hold data read from the zip file.  
 	char read_buffer[READ_SIZE]{'0'};

 	for (auto i = 0; i < global_info.number_entry; ++i)
 	{
 		// Get info about current file.  
 		unz_file_info file_info;
 		char filename[MAX_FILENAME]{'0'};
 		
 		if (unzGetCurrentFileInfo(
 			zipfile,
 			&file_info,
 			filename,
 			MAX_FILENAME,
 			nullptr, 0, nullptr, 0) != UNZ_OK)
 		{
 			std::cout <<"could not read file info\n";
 			unzClose(zipfile);
 			return;
 		}

 		// Check if this entry is a directory or file.  
 		if(!path(filename).has_extension())
 		{
 			FileTool::CreateDir(path(filename));
 		}
 		else
 		{
 			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
 			{
 				printf("could not open file\n");
 				unzClose(zipfile);
 				return;
 			}

 			// Open a file to write out the data.  
 			FileTool::CreateDir(path(filename).parent_path());
 			
 			FILE* out = fopen(filename, "wb");
 			if (out == nullptr)
 			{
 				printf("could not open destination file\n");
 				unzCloseCurrentFile(zipfile);
 				unzClose(zipfile);
 				return ;
 			}

 			int error = UNZ_OK;
 			do
 			{
 				error = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);
 				if (error < 0)
 				{
 					printf("error %d\n", error);
 					unzCloseCurrentFile(zipfile);
 					unzClose(zipfile);
 					return;
 				}

 				// Write data to file.  
 				if (error > 0)
 				{
 					fwrite(read_buffer, error, 1, out); // You should check return of fwrite...  
 				}
 			} 
 			while (error > 0);

 			fclose(out);
 		}

 		unzCloseCurrentFile(zipfile);

 		// Go the the next entry listed in the zip file.  
 		if (i + 1 < global_info.number_entry)
 		{
 			if (unzGoToNextFile(zipfile) != UNZ_OK)
 			{
 				printf("cound not read next file\n");
 				unzClose(zipfile);
 				return ;
 			}
 		}
 	}

 	unzClose(zipfile);
 }

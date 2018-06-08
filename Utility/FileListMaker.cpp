#include "FileListMaker.h"
#include <filesystem>
#include <iostream>
#include "md5.h"
#include <fstream>
#include <cassert>
#include <utility>

namespace Utility
{
	FileListMaker::FileListMaker(const std::string& path, int version)
	{
		_FileListData.Version = version;
		
		_GetAllFile(path);
	}

	FileListMaker::~FileListMaker()
	{
	}

	void FileListMaker::_GetAllFile(const std::string& path)
	{
		namespace fs = std::experimental::filesystem;

		for (auto& p : fs::directory_iterator(path))
		{
			auto& fp = p.path();
			
			_ReadFile(fp.relative_path().string());
			
			_CreateMD5();
			
			_FileListData.Contents.emplace_back(fp.relative_path().string(), _MD5);
		}

		_WriteFile();
	}

	void FileListMaker::_ReadFile(const std::string&& relative_path)
	{
		std::ifstream infile(relative_path, std::ios::in | std::ios::ate); //read mode | read to end

		if (!infile.is_open())
		{
			int i = 0;
			assert("open file error, testfile.txt");
			return;
		}

		const auto size = infile.tellg();

		_Buffer.resize(size);

		infile.seekg(0);
		infile.read(reinterpret_cast<char*>(_Buffer.data()), size);
		infile.close();
	}

	void FileListMaker::_CreateMD5()
	{
		MD5 md5;
		md5.update(_Buffer.data(), _Buffer.size());
		md5.finalize();
		_MD5 = md5.hexdigest();
	}

	void FileListMaker::_WriteFile()
	{
		std::ofstream outfile("filelist-2.txt", std::ofstream::out); //write mode | write data from eof 

		//std::ofstream outfile("filelist-2.txt", std::ofstream::out | std::ofstream::app); //write mode | write data from eof 

		outfile << "buildversion=" << _FileListData.Version << std::endl;

		for(auto& c : _FileListData.Contents)
		{
			outfile << c.Path << "|" << c.MD5 << std::endl;
		}

		outfile.close();
	}
}

#include "FileListMaker.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include "../Utility/md5.h"

namespace FileListMaker
{
	FileListMaker::FileListMaker(std::string input_path, std::string output_path, int version)
		:_InputPath(std::move(input_path))
		,_OutputPath(std::move(output_path))
		, _Version(version)
	{
		_CreateDirectory();
		_FileListData.Version = version;
		_ScanInputPath();
	}

	void FileListMaker::_CreateDirectory()
	{
		namespace fs = std::experimental::filesystem;
		fs::create_directories(_OutputPath);
	}

	void FileListMaker::_ScanInputPath()
	{
		namespace fs = std::experimental::filesystem;

		for (auto& p : fs::directory_iterator(_InputPath))
		{
			auto& fp = p.path();
			
			_ReadFile(fp.relative_path().string());
			
			_CreateMD5();
			
			//_FileListData.Contents.emplace(_MD5, fp.relative_path().string());
		}

		_ComparisonLastVer();

		_CreateFileList();
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


	void FileListMaker::_ComparisonLastVer()
	{
	}

	void FileListMaker::_CreateFileList()
	{
		const auto fileName = std::to_string(_Version) + "filelist.txt";
		const std::experimental::filesystem::path p1(_OutputPath);
		auto p2 = p1 / fileName;

		std::ofstream outfile(p2.string(), std::ofstream::out); //write mode

		outfile << "buildversion=" << _FileListData.Version << std::endl;

		for(auto& c : _FileListData.Contents)
		{
			outfile << c.first << "|" << c.second.Path << std::endl;
		}

		outfile.close();
	}
}

#pragma once
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "md5.h"

class FileTool
{
public:
	FileTool();
	~FileTool();

	static _off_t GetFileSize_C(std::string& path)
	{
		struct stat fileStat{};

		const _off_t ret = stat(path.c_str(), &fileStat);
		
		if (ret == 0)
		{
			return fileStat.st_size;
		}
		return ret;
	}

	static std::ifstream::pos_type GetFileSize_CPlusPlus(std::string& filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	static bool ReadFileToBuffer(const std::string& file_path, std::vector<char>& buffer)
	{
		std::ifstream infile(file_path, std::ios::in | std::ios::ate); //read mode | read to end

		if (!infile.is_open())
		{
			//assert("open file error, testfile.txt");
			return false;
		}

		const auto size = infile.tellg();

		buffer.resize(size);

		infile.seekg(0);
		infile.read(buffer.data(), size);
		infile.close();
		
		return true;
	}

	static std::string CreateMD5(std::vector<char>& buffer)
	{
		MD5 md5;
		md5.update(reinterpret_cast<unsigned char*>(buffer.data()), buffer.size());
		md5.finalize();
		return md5.hexdigest();
	}
};


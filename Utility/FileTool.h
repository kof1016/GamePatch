#pragma once
#include <sys/stat.h>
#include <string>
#include <fstream>

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
};


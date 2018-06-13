#include "FileReader.h"
#include <cassert>
#include <vector>
#include <fstream>
#include "ConfigParser.h"


namespace Utility
{
	FileReader::FileReader()
	{
		_Buffer.resize(1,'\0');

	}

	FileReader::~FileReader()
	{
	}

	DataDefine::FileListData FileReader::ReadFile(const std::string& file_name)
	{
		_ReadFile(file_name);
		_ParserData();
		return _FileListData;
	}

	// DataDefine::FileListData FileReader::GetFileList() const
	// {
	// 	return _FileListData;
	// }

	void FileReader::_ReadFile(const std::string& file_name)
	{
		std::ifstream infile(file_name, std::ios::in | std::ios::ate); //read mode | read to end

		if (!infile.is_open())
		{
			//assert("open file error, testfile.txt");
			return;
		}

		const auto size = infile.tellg();

		_Buffer.resize(size);

		infile.seekg(0);
		infile.read(_Buffer.data(), size);
		infile.close();
	}

	void FileReader::_ParserData()
	{
		ConfigParser parser;
		_FileListData = parser.Load(_Buffer.data());
		
		
	}
}

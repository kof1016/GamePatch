#include "FileListReader.h"
#include <fstream>
#include "../Utility/ConfigParser.h"


namespace FileListMaker
{
	FileListReader::FileListReader()
	{
		_Buffer.resize(1,'\0');

	}

	FileListReader ::~FileListReader()
	{
	}

	DataDefine::FileListData FileListReader::ReadFile(const std::string& file_name)
	{
		_ReadFile(file_name);
		_ParserData();
		return _FileListData;
	}

	void FileListReader::_ReadFile(const std::string& file_name)
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

	void FileListReader::_ParserData()
	{
		Utility::ConfigParser parser;
		_FileListData = parser.Load(_Buffer.data());
		
		
	}
}

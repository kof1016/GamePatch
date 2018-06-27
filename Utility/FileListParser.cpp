#include "FileListParser.h"
#include <regex>
#include <iostream>

namespace Utility
{
	FileListParser::FileListParser()
	{
	}


	FileListParser::~FileListParser()
	{
		//std::regex reg("(buildversion=[0-9]+)");
	}

	FileList FileListParser::Parser(const std::string& data)
	{
		const auto r = ParserVersion(data);

		_ParserFileAllData(r);

		_Debug();

		return _FileListData;
	}

	std::string FileListParser::ParserVersion(const std::string& data)
	{
		const std::regex reg("ver=([0-9]+)");

		std::smatch sm;

		if (regex_search(data, sm, reg))
		{
			_FileListData.Version = std::stoi(sm[1].str());
			return sm.suffix().str();
		}
		return "";
	}

	void FileListParser::_ParserFileAllData(const std::string& data)
	{
		//const std::regex reg(R"(([\w\/.]+)\|([0-9a-fA-F]{32}))");
		const std::regex reg(R"((\W)\|([0-9a-fA-F]{32})\|([\w\/.]+))");

		std::smatch sm;

		auto result{data};

		while (regex_search(result, sm, reg))
		{
			FileList::Content c{sm[1].str(), sm[2].str(), sm[3].str()};
			_FileListData.Contents.push_back(c);
			result = sm.suffix().str();
		}
	}

	void FileListParser::_Debug()
	{
		std::cout << std::endl;
		std::cout << "parser result:" << std::endl;
		std::cout << "version = " << _FileListData.Version << std::endl;
		std::cout << "==============contents=========== " << std::endl;
		for (auto& c : _FileListData.Contents)
		{
			std::cout << "md5 = " << c.MD5 << std::endl;
			std::cout << "path = " << c.Path << std::endl;
		}
	}
}

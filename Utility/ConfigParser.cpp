#include "ConfigParser.h"
#include <regex>
#include <iostream>

namespace Utility
{
	ConfigParser::ConfigParser()
	{
	}


	ConfigParser::~ConfigParser()
	{
		std::regex reg("(buildversion=[0-9]+)");
	}

	DataDefine::FileListData ConfigParser::Load(const std::string& data)
	{
		const auto r = _ParserVersion(data);

		_ParserFilePath(r);

		_Debug();

		return _FileListData;
	}

	std::string ConfigParser::_ParserVersion(const std::string& data)
	{
		const std::regex reg("buildversion=([0-9]+)");

		std::smatch sm;

		regex_search(data, sm, reg);

		_FileListData.Version = std::stoi(sm[1].str());

		return sm.suffix().str();
	}

	void ConfigParser::_ParserFilePath(const std::string& data)
	{
		const std::regex reg(R"(([\w\/.]+)\|([0-9a-fA-F]{32}))");

		std::smatch sm;
		
		auto result{data};

		while (regex_search(result, sm, reg))
		{
			_FileListData.Contents.emplace_back(sm[1].str(), sm[2].str());
			result = sm.suffix().str();
		}
	}

	void ConfigParser::_Debug()
	{
		std::cout << "parser result:" << std::endl;
		std::cout << "version = " << _FileListData.Version << std::endl;
		std::cout << "==============contents=========== " << std::endl;
		for (auto& c : _FileListData.Contents)
		{
			std::cout << "path = " << c.Path << std::endl;
			std::cout << "md5 = " << c.MD5 << std::endl;
		}
	}
}

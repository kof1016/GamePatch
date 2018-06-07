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
		_ParserVersion(data);
		return {};
	}

	void ConfigParser::_ParserVersion(const std::string& data)
	{
		const std::regex reg("buildversion=([0-9]+)");

		std::smatch sm;

		auto result{data};
		
		regex_search(result, sm, reg);
		for (const auto& r : sm)
		{
			std::cout << r.str() << std::endl;
		}

		_FileListData.Version = std::stoi(sm[1].str());
		result = sm.suffix().str();
			
		_ParserFilePath(result);
		
	}

	void ConfigParser::_ParserFilePath(const std::string& data)
	{
		const std::regex reg(R"(([\w\/.]+)\|([0-9a-fA-F]{32}))");

		std::smatch sm;
		auto result{ data };
		
		while (regex_search(result, sm, reg))
		{
			_FileListData._Contents.emplace_back(sm[1].str(), sm[2].str().c_str()) ;

			for (const auto& r : sm)
			{
				std::cout << r.str() << std::endl;
			}

			result = sm.suffix().str();
		}
	}
}

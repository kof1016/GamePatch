#include "DataParser.h"
#include <regex>
#include "FileTool.h"

namespace BZbee::Sandbox::GamePatch::Utility::File
{
	int DataParser::ParserVersionNumberByFile(const std::string& file_path)
	{
		std::vector<char> buffer{ 1, '\0' };
		ReadFileToBuffer(file_path, buffer);

		return ParserVersionNumber(buffer.data());
	}

	int DataParser::ParserVersionNumber(const std::string& data)
	{
		const std::regex reg("ver=([0-9]+)");
		std::smatch sm;

		if (regex_search(data, sm, reg))
		{
			const int verNumber = std::stoi(sm[1].str());
			return verNumber;
		}
		return 0;
	}

	DataDefine::FileList DataParser::ParserFileListByFile(const std::string& file_path)
	{
		std::vector<char> buffer{ 1, '\0' };
		ReadFileToBuffer(file_path, buffer);
		
		return ParserFileList(buffer.data());
		
	}

	DataDefine::FileList DataParser::ParserFileList(const std::string& data)
	{
		const std::regex reg(R"((\W)\|([0-9a-fA-F]{32})\|([\w\/.]+))");

		std::smatch sm;

		DataDefine::FileList fileList;

		auto result{data};

		while (regex_search(result, sm, reg))
		{
			DataDefine::FileData c{sm[1].str(), sm[2].str(), sm[3].str()};
			fileList.push_back(c);
			result = sm.suffix().str();
		}

		return fileList;
	}
}

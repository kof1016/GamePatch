#pragma once
#include "IParser.h"

namespace Utility
{
	class ConfigParser : public IParser
	{
	public:
		ConfigParser();
		virtual ~ConfigParser();
		DataDefine::FileListData Load(const std::string& data) override;
		void _Debug();
	private:
		std::string _ParserVersion(const std::string& data);
		void _ParserFilePath(const std::string& data);
		void _ParserMd5(const std::string& data);

		DataDefine::FileListData _FileListData;
	};
}

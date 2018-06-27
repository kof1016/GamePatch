#pragma once
#include "IParser.h"

namespace Utility
{
	class FileListParser : public IParser
	{
	public:
		FileListParser();
		virtual ~FileListParser();
		FileList Parser(const std::string& data) override;
		std::string _ParserFileState(const std::string& data);
		std::string ParserVersion(const std::string& data);
		
	private:
		void _ParserFileAllData(const std::string& data);
		void _Debug();
		FileList _FileListData;
	};
}

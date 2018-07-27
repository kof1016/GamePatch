#pragma once
#include "IParser.h"

namespace Utility
{
	class DataParser
	{
	public:
		static int ParserVersionNumberByFile(const std::string& file_path);
		static int ParserVersionNumber(const std::string& data);

		static FileList ParserFileListByFile(const std::string& file_path);
		static FileList ParserFileList(const std::string& pack_path);
	};
}

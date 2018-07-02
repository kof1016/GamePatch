#pragma once
#include "IParser.h"

namespace Utility
{
	class DataParser
	{
	public:
		static int ParserVersionNumber(const std::string& pack_path);
		static FileList ParserFileList(const std::string& pack_path);
	};
}

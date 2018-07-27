#pragma once
#include "IParser.h"

namespace BZbee::Sandbox::GamePatch::Utility::File
{
	class DataParser
	{
	public:
		static int ParserVersionNumberByFile(const std::string& file_path);
		static int ParserVersionNumber(const std::string& data);

		static DataDefine::FileList ParserFileListByFile(const std::string& file_path);
		static DataDefine::FileList ParserFileList(const std::string& pack_path);
	};
}

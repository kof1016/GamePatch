#pragma once
#include <string>
#include <vector>
#include "FileListMaker.h"

namespace Utility
{
	class FileReader final
	{
	public:
		FileReader();
		~FileReader();

		DataDefine::FileListData ReadFile(const std::string& file_name);
		

	private:
		void _ReadFile(const std::string& file_name);
		void _ParserData();
		std::vector<char> _Buffer;
		DataDefine::FileListData _FileListData;
	};
}

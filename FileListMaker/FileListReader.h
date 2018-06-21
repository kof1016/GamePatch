#pragma once
#include <string>
#include <vector>
#include "../Utility/DataDefine.h"

namespace FileListMaker
{
	class FileListReader final
	{
	public:
		FileListReader();
		~FileListReader();

		DataDefine::FileListData ReadFile(const std::string& file_name);
		

	private:
		void _ReadFile(const std::string& file_name);
		void _ParserData();
		std::vector<char> _Buffer;
		DataDefine::FileListData _FileListData;
	};
}

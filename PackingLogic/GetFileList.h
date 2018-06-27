#pragma once
#include "../Utility/DataDefine.h"
#include "../Utility/FileListParser.h"
#include <vector>

namespace PackingLogic
{
	class GetFileList
	{
	public:
		GetFileList() = delete;
		GetFileList(std::string pack_path);
		~GetFileList();
		Utility::FileList Result();
	private:

		std::string _Path;
		std::vector<char> _Buffer{ 1,'\0' };
		Utility::FileListParser _Parser;
	};

}

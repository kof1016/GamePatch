#pragma once
#include "../Utility/DataDefine.h"
#include "../Utility/FileListParser.h"

namespace FileListMaker
{
	class GetFileList
	{
	public:
		GetFileList(std::string pack_path);
		~GetFileList();
		DataDefine::FileList Result();
	private:

		std::string _Path;
		std::vector<char> _Buffer{ 1,'\0' };
		Utility::FileListParser _Parser{};
	};

}

#include "GetFileList.h"
#include <utility>
#include "../Utility/FileTool.h"
#include <filesystem>


namespace PackingLogic
{
	GetFileList::GetFileList(std::string path)
		:_Path(std::move(path))
	{
	}

	GetFileList::~GetFileList()
	{
	}

	Utility::FileList GetFileList::Result()
	{
		 FileTool::ReadFileToBuffer(_Path, _Buffer);
		 return _Parser.Parser(_Buffer.data());
	}
}

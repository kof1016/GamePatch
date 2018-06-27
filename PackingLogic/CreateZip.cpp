#include "CreateZip.h"
#include "../Utility/FileTool.h"
#include <filesystem>
#include "DataDefine.h"

namespace PackingLogic
{
	CreateZip::CreateZip(std::list<Utility::FileList::Content> file_list)
		:_FileList(std::move(file_list))
	{
	}

	CreateZip::~CreateZip()
	{
	}

	void CreateZip::Start()
	{
	}
}

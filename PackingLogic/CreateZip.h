#pragma once
#include "../Utility/DataDefine.h"
#include <list>

namespace PackingLogic
{
	class CreateZip
	{
	public:
		CreateZip(std::list<Utility::FileList::Content> file_list);
		~CreateZip();
		void Start();
	
	private:
		std::list<Utility::FileList::Content> _FileList;
		std::string _Path;
		int _Ver;
	};
}

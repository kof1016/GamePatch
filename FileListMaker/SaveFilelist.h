#pragma once
#include "../Utility/FileListParser.h"
#include <string>

namespace PackingLogic
{
	class SaveFileList
	{
	public:
		SaveFileList(int ver, std::list<DataDefine::FileList::Content>& file_list);
		~SaveFileList();
		bool Save();

	private:
		void _CreateFileList();
		int _Ver;
		std::list<DataDefine::FileList::Content> _FileList;
		std::string _Path;
	};

}

#pragma once
#include "../Utility/FileListParser.h"
#include <string>
#include <list>

namespace PackingLogic
{
	class CreateFileListToFile
	{
	public:
		CreateFileListToFile(int ver, std::list<Utility::FileList::Content>& file_list);
		~CreateFileListToFile();
		std::list<Utility::FileList::Content> Create();

	private:
		void _CheckDirExists();
		void _CreateFile();
		int _Ver;
		std::list<Utility::FileList::Content> _FileList;
		std::string _Path;
	};

}

#pragma once
#include <string>
#include <vector>
#include "../Utility/DataDefine.h"

namespace FileListMaker
{
	class ScanResourcePath
	{
	public:
		ScanResourcePath(std::string& resource_path, DataDefine::FileList& current_file_list);
		~ScanResourcePath();

		int Result();
		void _CreateMD5();
		void _CreateFileList();

	private:
		int _Ver;
		std::string _ResourcePath;
		std::vector<char> _Buffer{ 1,'\0' };
		std::string _MD5;
		DataDefine::FileList _CurrentFileList;
		DataDefine::FileList _NewFileList;

	};

}

#pragma once
#include "../Utility/DataDefine.h"
#include "../Utility/cpplinq.hpp"


namespace FileListMaker
{
	class MergeFileList
	{
	public:
		MergeFileList(DataDefine::FileList& current, DataDefine::FileList& all_source);
		~MergeFileList();

		std::list<DataDefine::FileList::Content> Result();

	private:
		DataDefine::FileList _Current;
		DataDefine::FileList _AllSource;
	};
}

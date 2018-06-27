#pragma once
#include "../Utility/DataDefine.h"
#include "../Utility/cpplinq.hpp"


namespace PackingLogic
{
	class MergeFileList
	{
	public:
		MergeFileList(Utility::FileList& current, Utility::FileList& all_source);
		~MergeFileList();

		std::list<Utility::FileList::Content> Result();

	private:
		Utility::FileList _Current;
		Utility::FileList _AllSource;
	};
}

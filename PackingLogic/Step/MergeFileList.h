#pragma once
#include "../../Utility/DataDefine.h"
#include "../../Utility/Linq/cpplinq.hpp"


namespace PackingLogic
{
	class MergeFileList
	{
	public:
		MergeFileList(Utility::FileList current, Utility::FileList all_source);
		~MergeFileList();

		Utility::FileList Result();

	private:
		Utility::FileList _Current;
		Utility::FileList _AllSource;
	};
}

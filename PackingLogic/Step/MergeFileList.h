#pragma once
#include "../../Utility/DataDefine.h"
#include "../../Utility/Linq/cpplinq.hpp"


namespace bZbee::Sandbox::GamePatch::PackingLogic::Step
{
	class MergeFileList
	{
	public:
		MergeFileList(Utility::DataDefine::FileList current, Utility::DataDefine::FileList all_source);
		~MergeFileList();

		Utility::DataDefine::FileList Result();

	private:
		Utility::DataDefine::FileList _Current;
		Utility::DataDefine::FileList _AllSource;
	};
}

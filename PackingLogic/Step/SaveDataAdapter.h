#pragma once
#include <vector>
#include "../../Utility/DataDefine.h"

namespace BZbee::Sandbox::GamePatch::PackingLogic::Step
{
	class SaveDataAdapter final
	{

	public:
		SaveDataAdapter() = delete;
		SaveDataAdapter(Utility::DataDefine::FileList merge_list, int newest_ver);
		~SaveDataAdapter();
		Utility::DataDefine::SaveList Adapter();
	private:
		Utility::DataDefine::FileList _MergeList;
		int _NewestVer;
		Utility::DataDefine::SaveList _SaveList;
	};
}

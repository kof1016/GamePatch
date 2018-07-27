#pragma once
#include <vector>
#include "../../Utility/DataDefine.h"

namespace PackingLogic
{
	class SaveDataAdapter final
	{

	public:
		SaveDataAdapter() = delete;
		SaveDataAdapter(Utility::FileList merge_list, int newest_ver);
		~SaveDataAdapter();
		Utility::SaveList Adapter();
	private:
		Utility::FileList _MergeList;
		int _NewestVer;
		Utility::SaveList _SaveList;
	};
}

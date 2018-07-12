#pragma once
#include <vector>
#include "../Utility/DataDefine.h"

namespace PackingLogic
{
	class FilterDataToSave final
	{

	public:
		FilterDataToSave() = delete;
		FilterDataToSave(Utility::FileList merge_list, int newest_ver);
		~FilterDataToSave();
		Utility::SaveList Filter();
	private:
		Utility::FileList _MergeList;
		int _NewestVer;
		Utility::SaveList _Filter;
	};
}

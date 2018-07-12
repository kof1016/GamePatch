#include "FilterDataToSave.h"
#include <utility>

namespace PackingLogic
{
	FilterDataToSave::FilterDataToSave(Utility::FileList merge_list, int newest_ver)
		:_MergeList(std::move(merge_list))
		,_NewestVer(newest_ver)
	{
	}

	FilterDataToSave::~FilterDataToSave()
	{
	}

	Utility::SaveList FilterDataToSave::Filter()
	{
		auto path = Utility::FileListSavePath(_NewestVer);
		_Filter.push_back({path.string()});

		for (auto& a : _MergeList)
		{
			_Filter.push_back({ a.Path });
		}
		return _Filter;
	}
}

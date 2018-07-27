#include "SaveDataAdapter.h"
#include <utility>

namespace PackingLogic
{
	SaveDataAdapter::SaveDataAdapter(Utility::FileList merge_list, int newest_ver)
		:_MergeList(std::move(merge_list))
		,_NewestVer(newest_ver)
	{
	}

	SaveDataAdapter::~SaveDataAdapter()
	{
	}

	Utility::SaveList SaveDataAdapter::Adapter()
	{
		auto path = Utility::FileListSavePath(_NewestVer);
		_SaveList.push_back({path.string()});

		for (auto& a : _MergeList)
		{
			_SaveList.push_back({ a.Path });
		}
		return _SaveList;
	}
}

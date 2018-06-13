#include "FindDiffState.h"
#include <utility>

namespace Logic
{
	FindDiffState::FindDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote)
		:_Local(std::move(local)),
		_Remote(std::move(remote))
	{
	}

	FindDiffState::~FindDiffState()
	{
	}

	void FindDiffState::Enter()
	{
		DataDefine::FileListData::FilelistContent diffs;

		for (auto& e : _Remote->Contents)
		{
			const auto r = _Local->Contents.find(e.first);
			
			if (r == _Local->Contents.end())
			{
				diffs.insert(e);
			}
		}

		const DataDefine::FileListData::ShareContent content(&diffs);

		_OnDone(content);
	}

	void FindDiffState::Leave()
	{
	}

	void FindDiffState::Update()
	{
	}

	void FindDiffState::OnDoneEvent(OnDone&& callback)
	{
		_OnDone = callback;
	}
}

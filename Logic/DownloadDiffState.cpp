#include "DownloadDiffState.h"

namespace Logic
{
	DownloadDiffState::DownloadDiffState(DataDefine::FileListData::ShareContent contents)
		:_Contents(std::move(contents))
	{
	}


	DownloadDiffState::~DownloadDiffState()
	{
	}

	void DownloadDiffState::Enter()
	{
		
	}

	void DownloadDiffState::Leave()
	{
	}

	void DownloadDiffState::Update()
	{
	}

	void DownloadDiffState::OnDoneEvent(OnDone&& callback)
	{
		_OnDone = callback;
	}
}

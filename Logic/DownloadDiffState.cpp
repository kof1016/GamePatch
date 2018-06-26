#include "DownloadDiffState.h"

namespace UpdateLogic
{
	DownloadDiffState::DownloadDiffState(DataDefine::FileList::Content contents)
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

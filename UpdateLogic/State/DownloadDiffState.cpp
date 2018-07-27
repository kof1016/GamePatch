#include "DownloadDiffState.h"

namespace UpdateLogic
{
	DownloadDiffState::DownloadDiffState(Utility::FileList file_list)
		:_FileList(std::move(file_list))
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

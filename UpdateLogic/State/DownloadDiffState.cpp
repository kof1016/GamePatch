#include "DownloadDiffState.h"

namespace BZbee::Sandbox::GamePatch::UpdateLogic::State
{
	DownloadDiffState::DownloadDiffState(Utility::DataDefine::FileList file_list)
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

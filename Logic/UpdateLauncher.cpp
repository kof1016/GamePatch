#include "UpdateLauncher.h"
#include "../Utility/HttpDownload.h"
#include "../Utility/StateMachine.h"
#include "GetRemoteFileState.h"
#include "ParserFilelistState.h"
#include "FindDiffState.h"

namespace Logic
{
	UpdateLauncher::UpdateLauncher()
	{
	}


	UpdateLauncher::~UpdateLauncher()
	{
	}

	void UpdateLauncher::Start()
	{
		_ToGetRemoteFileState();
	}

	void UpdateLauncher::_ToGetRemoteFileState()
	{
		Utility::HttpDownload download; //user
		const auto facade = download.Start("123");
		const Utility::FileWriter fileWriter("new-filelist");

		auto dfs = new GetRemoteFileState(facade, fileWriter);
		dfs->DoneEvent([&]()
		{
			_ToCompareFileState();
		});

		const std::shared_ptr<Utility::IState> state(dfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToCompareFileState()
	{
		const auto pfs = new ParserFilelistState();

		pfs->DoneEvent([&](auto local, auto remote)
		{
			if (local->Version != remote->Version)
			{
				_ToFindDiffState(local, remote);
			}
		});

		const std::shared_ptr<Utility::IState> state(pfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToFindDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote)
	{
		const auto fds = new FindDiffState(local, remote);
	}

	void UpdateLauncher::Update()
	{
		_StateMachine.Update();
	}
}

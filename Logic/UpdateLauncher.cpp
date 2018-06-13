#include "UpdateLauncher.h"
#include "../Utility/DownloadProvider.h"
#include "../Utility/StateMachine.h"
#include "DownloadFileState.h"
#include "ParserFilelistState.h"
#include "FindDiffState.h"
#include "DataDefine.h"
#include <filesystem>
#include <iostream>

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
		_ToDownloadFileState();
	}

	void UpdateLauncher::_ToDownloadFileState()
	{
		DataDefine::FileListData::ShareContent contents;

		const auto facade = _DownloadProvider.Start(PATH_SEVER_URL);
		Utility::FileWriter fileWriter(REMOTE_FILELIST_PATH);

		auto dfs = new DownloadFileState(facade, fileWriter);

		dfs->OnProgressEvent
		(
			[=](int total_size, int downloaded_size)
			{
				_OnProgress(total_size, downloaded_size);
			}
		);

		dfs->OnDoneEvent
		(
			[&]()
			{
				_ToParserFilelistState();
			}
		);

		const std::shared_ptr<Utility::IState> state(dfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToParserFilelistState()
	{
		const auto pfs = new ParserFilelistState();

		pfs->OnDoneEvent([&](auto local, auto remote)
		{
			_ToGetDiffState(local, remote);
		});

		const std::shared_ptr<Utility::IState> state(pfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToGetDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote)
	{
		const auto fds = new FindDiffState(local, remote);

		fds->OnDoneEvent([&](auto contents)
		{
			_ToDownloadDiffFileState(contents);
		});

		const std::shared_ptr<Utility::IState> state(fds);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToDownloadDiffFileState(DataDefine::FileListData::ShareContent contents)
	{
		//Utility::DownloadProvider download; //user

		// for (auto e : *contents)
		// {
		// 	const auto facade = download.Start(PATH_SEVER_URL);
		// 	Utility::FileWriter fileWriter(e.first);
		//
		// 	auto dfs = new DownloadFileState(facade, fileWriter);
		//
		// 	dfs->OnDoneEvent([&]()
		// 	{
		// 		//
		// 	});
		//
		// 	const std::shared_ptr<Utility::IState> state(dfs);
		// 	_StateMachine.Push(state);
		// }

		_ToMoveFile();
	}

	void UpdateLauncher::_ToMoveFile()
	{
		namespace fs = std::experimental::filesystem;

		fs::remove(LOCAL_FILELIST_PATH);
		fs::rename(REMOTE_FILELIST_PATH, LOCAL_FILELIST_PATH);
	}


	void UpdateLauncher::Update()
	{
		_StateMachine.Update();
	}

	void UpdateLauncher::Shutdown()
	{
	}

	void UpdateLauncher::OnDownloadProgress(DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
	}
}

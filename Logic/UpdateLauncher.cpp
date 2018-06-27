#include "UpdateLauncher.h"
#include "DownloadFileState.h"
#include "ParserFilelistState.h"
#include "FindDiffState.h"
#include "DataDefine.h"
#include <filesystem>
#include <iostream>

namespace UpdateLogic
{
	UpdateLauncher::UpdateLauncher()
	{
	}


	UpdateLauncher::~UpdateLauncher()
	{
	}

	void UpdateLauncher::Start()
	{
		_FilePaths.emplace(R"(..\resources\)"+ TEST_FILE_NAME);

		_ToDownloadFileState();
	}

	void UpdateLauncher::_ToDownloadFileState()
	{
		const auto path = _FilePaths.front();

		const auto facade = _DownloadProvider.Start(PATH_SERVER_URL + TEST_FILE_NAME);
		Utility::FileWriter fileWriter(path);

		auto dfs = new DownloadFileState(facade, fileWriter);

		dfs->OnProgressEvent([=](int total_size, int downloaded_size)
		{
			_OnProgress(total_size, downloaded_size);
		});

		dfs->OnDoneEvent([&]()
		{
			_FilePaths.pop();

			if (_FilePaths.empty())
			{
				_ToParserFilelistState();
			}
			else
			{
				_ToDownloadFileState();
			}
		});

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

		pfs->OnFailEvent([&]()
		{
			_OnNotNeed();
		});

		const std::shared_ptr<Utility::IState> state(pfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToGetDiffState(const Utility::FileList& local, const Utility::FileList& remote)
	{
		const auto fds = new FindDiffState(local, remote);

		fds->OnDoneEvent([&](auto paths)
		{
			std::swap(paths, _FilePaths);
			_ToDownloadDiffFileState();
		});

		const std::shared_ptr<Utility::IState> state(fds);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToDownloadDiffFileState()
	{
		auto& path = _FilePaths.front();
		const auto facade = _DownloadProvider.Start(PATH_SERVER_URL + TEST_FILE_NAME);
		Utility::FileWriter fileWriter(path);

		auto dfs = new DownloadFileState(facade, fileWriter);

		dfs->OnProgressEvent([=](int total_size, int downloaded_size)
		{
			_OnProgress(total_size, downloaded_size);
		});

		dfs->OnDoneEvent([&]()
		{
			_FilePaths.pop();

			if (_FilePaths.empty())
			{
				_OnSuccess();
			}
			else
			{
				_ToDownloadDiffFileState();
			}
		});

		const std::shared_ptr<Utility::IState> state(dfs);
		_StateMachine.Push(state);
	}

	void UpdateLauncher::_ToMoveFile() const
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
		std::cout << "UpdateLauncher::Shutdown" << std::endl;
	}

	void UpdateLauncher::OnDownloadProgress(Utility::OnProgress&& callback)
	{
		_OnProgress = callback;
	}

	void UpdateLauncher::OnUpdateSuccessEvent(Utility::OnSuccess&& callback)
	{
		_OnSuccess = callback;
	}

	void UpdateLauncher::OnNotNeedEvent(Utility::OnNotNeed&& callback)
	{
		_OnNotNeed = callback;
	}
}

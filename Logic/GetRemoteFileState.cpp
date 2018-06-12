#include "GetRemoteFileState.h"
#include "../Utility/IDownloadable.h"
#include <iostream>
#include <fstream>

namespace Logic
{
	GetRemoteFileState::GetRemoteFileState(std::shared_ptr<Utility::ReceiverFacade> facade,
												const Utility::FileWriter& fileuser)
		: _ReceiverFacade(std::move(facade)),
		_FileUser(fileuser)
	{
	}

	GetRemoteFileState::~GetRemoteFileState()
	{
	}

	void GetRemoteFileState::Enter()
	{
		_FileUser.CloseFile();

		_ReceiverFacade->BindWriteData
		(
			[&](char* buffer, size_t nmemb)
			{
				_FileUser.Write(buffer, nmemb);
			}
		);

		_ReceiverFacade->BindProgress
		(
			[=](int total, int downloaded)
			{
				const auto percent = downloaded * 100.0 / total;
				std::cout << "percent=" << percent << "\r";
			}
		);

		bool done = false;
		_ReceiverFacade->BindReceiverDone
		(
			[&](bool result)
			{
				_OnDone();
			}
		);
	}

	void GetRemoteFileState::Leave()
	{
		_FileUser.CloseFile();
	}

	void GetRemoteFileState::Update()
	{
	}

	void GetRemoteFileState::DoneEvent(std::function<void()>&& callback)
	{
		_OnDone = callback;
	}
}

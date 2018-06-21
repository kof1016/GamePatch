#include "DownloadFileState.h"
#include "../Utility/IDownloadable.h"
#include <iostream>
#include <fstream>
#include <utility>

namespace Logic
{
	DownloadFileState::DownloadFileState(std::shared_ptr<Utility::ReceiverFacade> facade,
										Utility::FileWriter& file_writer)
		: _ReceiverFacade(std::move(facade)),
		_FileWriter(file_writer)
	{
	}

	DownloadFileState::~DownloadFileState()
	{
	}

	void DownloadFileState::Enter()
	{
		_FileWriter.OpenFile();

		_ReceiverFacade->BindWriteData
		(
			[&](char* buffer, size_t nmemb)
			{
				_FileWriter.Write(buffer, nmemb);
			}
		);

		_ReceiverFacade->BindProgress
		(
			[=](int total, int downloaded)
			{
				_OnProgress(total, downloaded);
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

	void DownloadFileState::Leave()
	{
		_FileWriter.CloseFile();
	}

	void DownloadFileState::Update()
	{
	}

	void DownloadFileState::OnDoneEvent(DoneEvent&& callback)
	{
		_OnDone = callback;
	}

	void DownloadFileState::OnProgressEvent(DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
	}
}

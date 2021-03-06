#include "DownloadFileState.h"
#include "../../Utility/HttpDownload/IDownloadable.h"
#include <iostream>
#include <fstream>
#include <utility>

namespace UpdateLogic
{
	DownloadFileState::DownloadFileState(std::shared_ptr<Utility::ReceiverFacade> facade,
										Utility::FileWriter& file_writer)
		: _ReceiverFacade(facade),
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
			
				_FileWriter.CloseFile();
				_OnDone();
				

			}
		);
	}

	void DownloadFileState::Leave()
	{
	}

	void DownloadFileState::Update()
	{
	}

	void DownloadFileState::OnDoneEvent(DoneEvent&& callback)
	{
		_OnDone = callback;
	}

	void DownloadFileState::OnProgressEvent(Utility::OnProgress&& callback)
	{
		_OnProgress = callback;
	}
}

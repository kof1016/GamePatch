#include "HttpDownloadTask.h"
#include <iostream>
#include <memory>

namespace Utility
{
	HttpDownloadTask::HttpDownloadTask(std::shared_ptr<ReceiverFacade> receiver_facade)
	{
		_ReceiverFacade = receiver_facade;

		_CurlHttp.BindWriteData
		(
			[&](char* buffer, size_t nmemb)
			{
				_ReceiverFacade->InvokeWriteData(buffer, nmemb);
			}
		);

		_CurlHttp.BindProgress
		(
			[=](int total_size, int downloaded_size)
			{
				_ReceiverFacade->InvokeProgress(total_size, downloaded_size);
			}
		);
	}

	HttpDownloadTask::~HttpDownloadTask()
	{
	}

	// std::shared_ptr<ReceiverFacade> HttpDownloadTask::GetReceiver()
	// {
	// 	return _ReceiverFacade;
	// }

	void HttpDownloadTask::Connect(std::string url)
	{
		 
		_CurlHttp.GetRemoteFileSize(url);

		try
		{
			_CurlHttp.Downloading(DataDefine::CurlInitData
				{
					url, //url
					false, //postMode
					"", //postcontent
					false, //DownloadRange
					true, //WriteToFile
					true, //DownloadProgress
					true, //Debug
					true, //CheckResult
				});
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			throw;
		}
	}

	void HttpDownloadTask::BindDownloadDone(DataDefine::OnReceiveDownloadDone&& callback)
	{
		_OnDownloadDone = callback;

		_CurlHttp.BindReceiveDone
		(
			[&](bool result)
			{
				_ReceiverFacade->InvokeDownloadDone(result);
				_OnDownloadDone(result);
			}
		);
	}
}

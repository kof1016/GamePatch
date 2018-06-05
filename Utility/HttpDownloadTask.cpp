#include "HttpDownloadTask.h"
#include <iostream>
#include <memory>

namespace Utility
{
	HttpDownloadTask::HttpDownloadTask(std::shared_ptr<ReceiverFacade> receiver_facade)
	{
		_ReceiverFacade = receiver_facade;

		_CurlHttp.bindWriteData
		(
			[&](char* buffer, size_t size, size_t nmemb)-> size_t
			{
				auto r = _ReceiverFacade->InvokeWriteData(buffer, size, nmemb);
				return r;
			}
		);

		_CurlHttp.bindProgress
		(
			[=](int total_size, int downloaded_size)-> int
			{
				auto r = _ReceiverFacade->InvokeProgress(total_size, downloaded_size);
				return r;
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

		_CurlHttp.bindReceiveDone
		(
			[&](bool result)
			{
				_ReceiverFacade->InvokeDownloadDone(result);
				_OnDownloadDone(result);
			}
		);
	}
}

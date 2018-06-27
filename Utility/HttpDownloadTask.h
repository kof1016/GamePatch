#pragma once
#include "CurlHttp.h"
#include "ReceiverFacade.h"
#include <memory>

namespace Utility
{
	class HttpDownloadTask final
	{
	public:
		HttpDownloadTask(std::shared_ptr<ReceiverFacade> receiver_facade);
		~HttpDownloadTask();

		void Connect(std::string url);
		void BindDownloadDone(OnReceiveDownloadDone&& callback);
		//std::shared_ptr<ReceiverFacade> GetReceiver();

	private:
		std::shared_ptr<ReceiverFacade> _ReceiverFacade;
		CurlHttp _CurlHttp;

		OnReceiveDownloadDone _OnDownloadDone;
	};
}

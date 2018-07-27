#pragma once
#include <memory>
#include "../Receive/ReceiverFacade.h"
#include "../Curl/CurlHttp.h"


namespace Utility
{
	class HttpDownloadTask final
	{
	public:
		HttpDownloadTask(std::shared_ptr<ReceiverFacade> receiver_facade);
		~HttpDownloadTask();

		void Connect(std::string url);
		void BindDownloadDone(Utility::OnReceiveDownloadDone&& callback);
		//std::shared_ptr<ReceiverFacade> GetReceiver();

	private:
		std::shared_ptr<ReceiverFacade> _ReceiverFacade;
		CurlHttp _CurlHttp;

		OnReceiveDownloadDone _OnDownloadDone;
	};
}

#pragma once
#include <memory>
#include "../Receive/ReceiverFacade.h"
#include "../Curl/CurlHttp.h"
#include "../../UpdateLogic/State/DownloadFileState.h"


namespace BZbee::Sandbox::GamePatch::Utility::HttpDownload
{
	class HttpDownloadTask final
	{
	public:
		HttpDownloadTask(std::shared_ptr<Receive::ReceiverFacade> receiver_facade);
		~HttpDownloadTask();

		void Connect(std::string url);
		void BindDownloadDone(DataDefine::OnReceiveDownloadDone&& callback);
		//std::shared_ptr<ReceiverFacade> GetReceiver();

	private:
		std::shared_ptr<Receive::ReceiverFacade> _ReceiverFacade;
		Curl::CurlHttp _CurlHttp;

		DataDefine::OnReceiveDownloadDone _OnDownloadDone;
	};
}

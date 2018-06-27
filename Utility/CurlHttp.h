#pragma once

#include "../curl/curl.h"
#include "WriteDataAdapter.h"
#include "ProgressAdapter.h"
#include "CurlDebug.h"

namespace Utility
{
	class CurlHttp final 
	{
	public:
		CurlHttp();
		~CurlHttp();
		
		void GetRemoteFileSize(std::string url);

		void Downloading(CurlInitData&& data);

		void BindWriteData(OnWriteData&& callback);
		void BindReceiveDone(OnReceiveDownloadDone&& callback);

		void BindProgress(OnProgress&& callback);

	private:
		void _SetUrl(std::string&& url);
		void _SetDownloadRange(int range);
		void _SetBasicParameter();
		void _SetPost(bool enable);
		void _Debug(bool enable);
		void _WirteToFile(bool enable);
		void _DownloadProgress(bool enable);
		void _Perform();
		void _CheckResult(bool enable) const;

		WriteDataAdapter _CurlWriteDataAdapter;
		ProgressAdapter _CurlProgressAdapter;
		CurlDebug _CurlDebug;

		CURL* _pCurl{nullptr};
		CURLcode _Result;

		OnReceiveDownloadDone _OnReceiveDone;
		curl_off_t _RemoteFileSize{-1};
	};
}

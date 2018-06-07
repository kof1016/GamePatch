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

		void Downloading(DataDefine::CurlInitData&& data);

		void BindWriteData(DataDefine::OnWriteData&& callback);
		void BindReceiveDone(DataDefine::OnReceiveDownloadDone&& callback);

		void BindProgress(DataDefine::OnProgress&& callback);

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

		DataDefine::OnReceiveDownloadDone _OnReceiveDone;
		curl_off_t _RemoteFileSize{-1};
	};
}

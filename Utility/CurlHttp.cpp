#include <iostream>
#include "CurlHttp.h"

namespace Utility
{
	CurlHttp::CurlHttp()
	{
		curl_global_init(CURL_GLOBAL_ALL);
		_pCurl = curl_easy_init();

		try
		{
			if (!_pCurl)
			{
				std::cout << "curl init error" << std::endl;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << "curl init error" << std::endl;
		}
	}

	CurlHttp::~CurlHttp()
	{
		/* always cleanup */
		curl_easy_cleanup(_pCurl);
		curl_global_cleanup();
	}

	void CurlHttp::GetRemoteFileSize(std::string url)
	{
		_RemoteFileSize = -1;
		auto curl = curl_easy_init();
		CURLcode aa = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 1); //只需要header头  
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1); //不需要body  

		if (curl_easy_perform(curl) == CURLE_OK)
		{
			curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_RemoteFileSize);
		}

		else
		{
			_RemoteFileSize = -1;
		}
		
		curl_easy_cleanup(curl);
	}

	void CurlHttp::Downloading(DataDefine::CurlInitData&& data)
	{
		//GetRemoteFileSize(data.Url);
		_pCurl = curl_easy_init();
		_SetUrl(std::move(data.Url));
		_SetPost(data.Post);
		_SetDownloadRange(data.DownloadRange);
		_WirteToFile(data.WriteToFile);
		_DownloadProgress(data.DownloadProgress);
		_Debug(data.Debug);

		_SetBasicParameter();

		

		_Perform();

		//curl_easy_getinfo(_pCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_RemoteFileSize);

		_CheckResult(data.CheckResult);
	}

	void CurlHttp::BindWriteData(DataDefine::OnWriteData&& callback)
	{
		_CurlWriteDataAdapter.Bind(std::move(callback));
	}

	void CurlHttp::BindReceiveDone(DataDefine::OnReceiveDownloadDone&& callback)
	{
		_OnReceiveDone = callback;
	}

	void CurlHttp::BindProgress(DataDefine::OnProgress&& callback)
	{
		_CurlProgressAdapter.Bind(std::move(callback));
	}

	void CurlHttp::_SetUrl(std::string&& url)
	{
		curl_easy_setopt(_pCurl, CURLOPT_URL, url.c_str());
	}

	void CurlHttp::_SetPost(bool enable)
	{
		// true = post 
		// false = get
		curl_easy_setopt(_pCurl, CURLOPT_POST, enable);

		//curl_easy_setopt(_pCurl, CURLOPT_COPYPOSTFIELDS, info->postContent.c_str());
	}

	void CurlHttp::_SetDownloadRange(int range)
	{
		// download by range
		//curl_easy_setopt(_pCurl, CURLOPT_RANGE, "100-");
	}


	void CurlHttp::_SetBasicParameter()
	{
		curl_easy_setopt(_pCurl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(_pCurl, CURLOPT_FAILONERROR, 1L);
		curl_easy_setopt(_pCurl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(_pCurl, CURLOPT_CONNECTTIMEOUT, 10);
		curl_easy_setopt(_pCurl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	}


	void CurlHttp::_WirteToFile(bool enable)
	{
		if (!enable)
		{
			return;
		}
		curl_easy_setopt(_pCurl, CURLOPT_WRITEFUNCTION, &WriteDataAdapter::CurlCallback);
		curl_easy_setopt(_pCurl, CURLOPT_WRITEDATA, &_CurlWriteDataAdapter);
	}

	void CurlHttp::_DownloadProgress(bool enable)
	{
		if (!enable)
		{
			return;
		}
		//download progress trigger by second
		curl_easy_setopt(_pCurl, CURLOPT_NOPROGRESS, 0L);
		//curl_easy_setopt(_pCurl, CURLOPT_PROGRESSFUNCTION, &ProgressAdapter::CurlCallback);
		curl_easy_setopt(_pCurl, CURLOPT_XFERINFOFUNCTION, &ProgressAdapter::CurlCallback);
		curl_easy_setopt(_pCurl, CURLOPT_PROGRESSDATA, &_CurlProgressAdapter);
	}

	void CurlHttp::_Debug(bool enable)
	{
		if (!enable)
		{
			return;
		}

		curl_easy_setopt(_pCurl, CURLOPT_DEBUGFUNCTION, &CurlDebug::OnCallback);
		curl_easy_setopt(_pCurl, CURLOPT_DEBUGDATA, &CurlDebug::DebugInfo);
	}

	void CurlHttp::_Perform()
	{
		_Result = curl_easy_perform(_pCurl);
	}

	void CurlHttp::_CheckResult(bool enable) const
	{
		if (enable)
		{
			if (_Result != CURLE_OK)
			{
				printf("res != CURLE_OK, sDebug[%s]\n", CurlDebug::DebugInfo.c_str());

				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(_Result));
			}
		}

		_OnReceiveDone(_Result == CURLE_OK);
	}
}

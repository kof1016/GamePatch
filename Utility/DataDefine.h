#pragma once
#include <string>
#include <functional>

namespace DataDefine
{
	struct CurlInitData
	{
		std::string Url{""};
		bool Post{ false };
		std::string postContent{ "" };
		bool DownloadRange{ false };
		bool WriteToFile{ true };
		bool DownloadProgress{true};
		bool Debug{true};
		bool CheckResult{true};
	};

	typedef std::function<size_t(char* buffer, size_t size, size_t nmemb)> OnWriteData;
	typedef std::function<int(int total_size, int downloaded_size)> OnProgresser;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;
}

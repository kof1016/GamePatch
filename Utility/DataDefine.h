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

	struct FileListData
	{
		struct Content
		{
			Content(const std::string& path, const char* buffer)
			{
				Path = path;
				memcpy(MD5, buffer, 32);
			}
			std::string Path{};
			char MD5[32]{};

		};
		int Version{0};
		std::vector<Content> _Contents;
	};


	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;
}

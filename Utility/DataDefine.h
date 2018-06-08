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
			Content(const std::string& path, const std::string& md5)
			{
				Path = path;
				MD5 = md5;
			}
			std::string Path{};
			std::string MD5{};

		};
		int Version{0};
		std::vector<Content> Contents;
	};


	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;
}

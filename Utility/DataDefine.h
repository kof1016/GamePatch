#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>

namespace Utility
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

	struct FileList
	{
		struct Content
		{
			Content(const std::string& md5, const std::string& path) 
			{
				StateSymbol = "";
				MD5 = md5;
				Path = path;
			}

			Content(const std::string& state, const std::string& md5, const std::string& path)
			{
				StateSymbol = state;
				MD5 = md5;
				Path = path;
			}
			
			std::string StateSymbol{};
			std::string MD5{};
			std::string Path{};
		};
		
		int Version{0};
		std::vector<Content> Contents;
	};
	
	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void()> OnSuccess;
	typedef std::function<void()> OnNotNeed;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;
}

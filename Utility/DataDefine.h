#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>

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
			enum FileState
			{
				NONE,
				ADD,
				REMOVE,
			};

			Content(const std::string& md5, const std::string& path, FileState state)
			{
				MD5 = md5;
				Path = path;
				State = state;
			}

			std::string GetFileState()
			{
				if (State == ADD)
				{
					return "+";
				}
				if (State == REMOVE)
				{
					return "-";
				}
				return "";
			}

			std::string MD5{};
			std::string Path{};
			FileState State{};
		};
		int Version{-1};
		//std::vector<Content> Contents;

		
		typedef std::unordered_map<std::string, Content> FilelistContent;
		typedef std::shared_ptr<FilelistContent> ShareContent;
		
		FilelistContent Contents;
	};
	
	typedef std::shared_ptr<FileListData> ShareFileList;


	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void()> OnSuccess;
	typedef std::function<void()> OnNotNeed;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;

}

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

	struct FileList
	{
		struct Content
		{
			enum FileState
			{
				NONE,
				ADD,
				REMOVE,
			};

			Content(const std::string& md5, const std::string& path)
			{
				SetState("");
				MD5 = md5;
				Path = path;
			}

			Content(const std::string& state, const std::string& md5, const std::string& path)
			{
				SetState(state);
				MD5 = md5;
				Path = path;
			}

			void SetState(const std::string& state)
			{
				if (state == "+")
				{
					State = ADD;
				}
				else if (state == "-")
				{
					State = REMOVE;
				}
				else
				{
					State = NONE;
				}
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

			FileState State{};
			std::string MD5{};
			std::string Path{};
			bool bChecked{ false };
		};
		void Find(const std::string& key)
		{
			const auto r = Contents.find(key);
			if(r != Contents.end())
			{
				r->second.bChecked = true;
			}
		}
		int Version{0};
		//std::vector<Content> Contents;

		
		typedef std::unordered_map<std::string, Content> FilelistContent;
		typedef std::shared_ptr<FilelistContent> ShareContent;
		
		FilelistContent Contents;
	};
	
	typedef std::shared_ptr<FileList> ShareFileList;


	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void()> OnSuccess;
	typedef std::function<void()> OnNotNeed;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;

}

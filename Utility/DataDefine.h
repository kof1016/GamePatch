#pragma once
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <filesystem>
#include <filesystem>

using namespace  std::experimental::filesystem;

namespace BZbee::Sandbox::GamePatch::Utility::DataDefine
{
	struct CurlInitData final
	{
		std::string Url{""};
		bool Post{false};
		std::string postContent{""};
		bool DownloadRange{false};
		bool WriteToFile{true};
		bool DownloadProgress{true};
		bool Debug{true};
		bool CheckResult{true};
	};


	struct FileData final
	{
		FileData() = delete;

		FileData(const std::string& path)
		{
			StateSymbol = "";
			MD5 = "";
			Path = path;
		}

		FileData(const std::string& md5, const std::string& path)
		{
			StateSymbol = "";
			MD5 = md5;
			Path = path;
		}

		FileData(const std::string& state, const std::string& md5, const std::string& path)
		{
			StateSymbol = state;
			MD5 = md5;
			Path = path;
		}

		std::string StateSymbol{};
		std::string MD5{};
		std::string Path{};
	};

	typedef std::list<FileData> FileList;

	typedef std::function<void(char* buffer, size_t total)> OnWriteData;
	typedef std::function<void(int total_size, int downloaded_size)> OnProgress;
	typedef std::function<void()> OnSuccess;
	typedef std::function<void()> OnNotNeed;
	typedef std::function<void(bool result)> OnReceiveDownloadDone;

	struct ZipSaveData
	{
		ZipSaveData() = delete;

		ZipSaveData(std::string path)
			: Path(std::move(path))
		{
			SaveName = Path;
		}

		ZipSaveData(std::string path, std::string save_name)
			: Path(std::move(path))
			, SaveName(std::move(save_name))
		{
		}

		std::string Path;
		std::string SaveName;
	};
	typedef std::vector<ZipSaveData> SaveList;

	/*
	 * const string
	 */
	const std::string PACKING_FOLDER_NAME = "ResourcePack";
	const std::string NEWESTVER_NAME = "NewestVer.txt";
	const std::string LOCALVER_NAME = "LocalVer.txt";

	const std::string RESOURCE_FOLDER_NAME = "Resource";

	namespace fs = std::experimental::filesystem;


	static path NewestVerSavePath()
	{
		return PACKING_FOLDER_NAME / NEWESTVER_NAME;
	}

	static path LocalVerSavePath()
	{
		return path(RESOURCE_FOLDER_NAME) / path(LOCALVER_NAME);
	}

	static path FileListSavePath(int ver)
	{
		return path(PACKING_FOLDER_NAME) / path("filelist_ver" + std::to_string(ver) + ".txt");
	}

	static path ZipFileSavePath(int ver)
	{
		return path(PACKING_FOLDER_NAME) / path("ver" + std::to_string(ver) + ".zip");
	}

	static path NewestVerFilePath()
	{
		return path(PACKING_FOLDER_NAME) / NEWESTVER_NAME;
	}

	 const path PATH_SERVER_URL{"http://127.0.0.1:8887"};
	
	 static std::string FilePathToUrl(const path& file_path)
	 {
		auto path = PATH_SERVER_URL.string() / file_path.string();

		std::string url = path.string();
		
	 	std::replace(url.begin(), url.end(), '\\', '/');
		return url;
	 }
}

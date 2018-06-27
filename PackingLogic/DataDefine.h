#pragma once
#include <string>
#include <filesystem>
#include "../Utility/FileTool.h"

namespace PackingLogic
{
	const std::string PACKING_FOLDER_NAME = "ResourcePack";
	const std::string NEWESTVER_NAME = "NewestVer.txt";

	const std::string RESOURCE_FOLDER_NAME = "Resource";


	static std::string GetCurrentFileListPath(int ver)
	{
		namespace fs = std::experimental::filesystem;
		const auto current = fs::current_path();
		auto filelistPath = current / PACKING_FOLDER_NAME / ("ver" + std::to_string(ver)) / ("filelist_" + ("ver" + std::
			to_string(ver) + ".txt"));
		return filelistPath.string();
	}

	static std::string GetNewestVerPath()
	{
		namespace fs = std::experimental::filesystem;
		const auto path = fs::current_path() / PACKING_FOLDER_NAME / NEWESTVER_NAME;
		return path.string();
	}

	static std::string GetResourcePath()
	{
		namespace fs = std::experimental::filesystem;
		const auto current = fs::current_path();
		auto path = current / RESOURCE_FOLDER_NAME;
		return path.string();
	}

	static void CreateDir(const std::string& path)
	{
		namespace fs = std::experimental::filesystem;

		if (!fs::exists(path))
		{
			fs::create_directories(path);
		}
	}
}

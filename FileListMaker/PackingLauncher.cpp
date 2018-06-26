#include "PackingLauncher.h"
#include "GetCurrentVer.h"
#include "GetFileList.h"
#include "MergeFileList.h"
#include <filesystem>
#include <string>
#include "FileListMaker.h"
#include "VersionUpdater.h"
#include "SaveFileList.h"
#include "CreateZip.h"


namespace FileListMaker
{
	PackingLauncher::PackingLauncher()
	{
	}

	PackingLauncher::~PackingLauncher()
	{
	}

	void PackingLauncher::Start()
	{
		//step1
		GetCurrentVer getCurrentVer;
		const auto ver = getCurrentVer.Result();

		//step2
		namespace fs = std::experimental::filesystem;
		auto current = fs::current_path();
		auto filelistPath = current / "ResourcePack" / ("ver" + std::to_string(ver))/ ("filelist_" + ("ver" + std::to_string(ver) + ".txt"));
		
		GetFileList getFileList(filelistPath.string());
		auto currentFileList = getFileList.Result();

		//step3
		namespace fs = std::experimental::filesystem;
		current = fs::current_path();
		auto input = current / "Resource";

		FileListMaker maker(input.string());
		auto allresourcefileList = maker.Make();

		//step4		
		MergeFileList merge(currentFileList, allresourcefileList);
		auto mergedlist = merge.Result();

		//step5
		VersionUpdater verUpdater;
		const auto newver = verUpdater.Update();

		//step6
		SaveFileList saveFilelist(newver, mergedlist);
		saveFilelist.Save();
		
		//step7
		CreateZip zip;
	}

	void PackingLauncher::Update()
	{
	}

	void PackingLauncher::Shutdown()
	{
	}
}

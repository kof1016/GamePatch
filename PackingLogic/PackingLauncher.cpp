#include "PackingLauncher.h"
#include "DataDefine.h"
#include "GetFileList.h"
#include "MergeFileList.h"
#include "VersionUpdater.h"
#include "CreateFileListToFile.h"
#include "CreateZip.h"
#include "ScanResourceFolder.h"


namespace PackingLogic
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
		CreateDir(GetNewestVerPath());
		
		//step2
		const auto currentVer = GetFileList(GetNewestVerPath()).Result().Version;

		//step3
		auto currentFileList = GetFileList(GetCurrentFileListPath(currentVer)).Result();

		//step4
		auto allresourcefileList = ScanResourceFolder(GetResourcePath()).Make();
		
		//step5		
		auto mergedList = MergeFileList(currentFileList, allresourcefileList).Result();

		//step6
		const auto newestVer = VersionUpdater().Update();
		
		//step7
		auto fileList = CreateFileListToFile(newestVer, mergedList).Create();

		//step8
		CreateZip(fileList).Start();
	}
}

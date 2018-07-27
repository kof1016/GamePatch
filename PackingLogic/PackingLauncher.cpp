#include "PackingLauncher.h"
#include "Step/MergeFileList.h"
#include "Step/VersionUpdater.h"
#include "Step/ScanResourceFolder.h"
#include "Step/WriteToFile.h"
#include "Step/SaveDataAdapter.h"
#include "../Utility/File/DataParser.h"
#include "../Utility/File/FileTool.h"

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
		FileTool::CreateDir(Utility::PACKING_FOLDER_NAME);
		
		//step2
		const auto currentVerNumber = Utility::DataParser::ParserVersionNumberByFile(Utility::NewestVerFilePath().string());

		//step3
		const auto currentVerFileList = Utility::DataParser::ParserFileListByFile(Utility::FileListSavePath(currentVerNumber).string());

		//step4
		const auto resourceFileList = ScanResourceFolder(path(Utility::RESOURCE_FOLDER_NAME).string()).Make();
		
		//step5		
		const auto mergedList = MergeFileList(currentVerFileList, resourceFileList).Result();

		//step6
		const auto newestVer = VersionUpdater(currentVerNumber).UpdateVer(); 

		//step7
		CreateNewestVerFile(Utility::NewestVerFilePath().string(), "ver=" + std::to_string(newestVer)).Write();
		
		//step8
		CreateFileListFile(Utility::FileListSavePath(newestVer).string(), mergedList).Write();

		//step9
		const auto savelist = SaveDataAdapter(mergedList, newestVer).Adapter();
		
		//step10
		FileTool::CreateZipFromSaveList(savelist, Utility::ZipFileSavePath(newestVer).string());
	}
}

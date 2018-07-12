#include "PackingLauncher.h"
#include "MergeFileList.h"
#include "VersionUpdater.h"
#include "ScanResourceFolder.h"
#include "WriteToFile.h"
#include "FilterDataToSave.h"

#include "../Utility/DataParser.h"
#include "../Utility/FileTool.h"

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
		WriteFileFromString(Utility::NewestVerFilePath().string(), "ver=" + std::to_string(newestVer)).Write();
		
		//step8
		WriteFileFromList(Utility::FileListSavePath(newestVer).string(), mergedList).Write();

		//step9
		const auto savelist = FilterDataToSave(mergedList, newestVer).Filter();
		
		//step10
		FileTool::CreateZipFromSaveList(savelist, Utility::ZipFileSavePath(newestVer).string());
	
	}
}

#include "PackingLauncher.h"
#include "Step/MergeFileList.h"
#include "Step/VersionUpdater.h"
#include "Step/ScanResourceFolder.h"
#include "Step/WriteToFile.h"
#include "Step/SaveDataAdapter.h"
#include "../Utility/File/DataParser.h"
#include "../Utility/File/FileTool.h"

namespace bZbee::Sandbox::GamePatch::PackingLogic::Launcher
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
		Utility::File::CreateDir(Utility::DataDefine::PACKING_FOLDER_NAME);
		
		//step2
		const auto currentVerNumber = Utility::File::DataParser::ParserVersionNumberByFile(Utility::DataDefine::NewestVerFilePath().string());

		//step3
		const auto currentVerFileList = Utility::File::DataParser::ParserFileListByFile(Utility::DataDefine::FileListSavePath(currentVerNumber).string());

		//step4
		const auto resourceFileList = Step::ScanResourceFolder(path(Utility::DataDefine::RESOURCE_FOLDER_NAME).string()).Make();
		
		//step5		
		const auto mergedList = Step::MergeFileList(currentVerFileList, resourceFileList).Result();

		//step6
		const auto newestVer = Step::VersionUpdater(currentVerNumber).UpdateVer(); 

		//step7
		Step::CreateNewestVerFile(Utility::DataDefine::NewestVerFilePath().string(), "ver=" + std::to_string(newestVer)).Write();
		
		//step8
		Step::CreateFileListFile(Utility::DataDefine::FileListSavePath(newestVer).string(), mergedList).Write();

		//step9
		const auto savelist = Step::SaveDataAdapter(mergedList, newestVer).Adapter();
		
		//step10
		Utility::File::CreateZipFromSaveList(savelist, Utility::DataDefine::ZipFileSavePath(newestVer).string());
	}
}

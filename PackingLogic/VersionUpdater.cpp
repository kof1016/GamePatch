#include "VersionUpdater.h"
#include "DataDefine.h"
#include "GetFileList.h"
#include "../Utility/FileWriter.h"


namespace PackingLogic
{
	VersionUpdater::VersionUpdater()
	{
	}


	VersionUpdater::~VersionUpdater()
	{
	}

	int VersionUpdater::Update()
	{
		const auto path = GetNewestVerPath();
		const auto newVer = GetFileList(path).Result().Version + 1;

		Utility::FileWriter writer(path);
		writer.OpenFile();

		const auto write = "ver=" + std::to_string(newVer);
		writer.Write(write.data(), write.size());

		writer.CloseFile();

		return newVer;
	}
}

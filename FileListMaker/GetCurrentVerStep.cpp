#include "GetCurrentVerStep.h"
#include "FileListCreator.h"
#include <filesystem>
namespace FileListMaker
{
	GetCurrentVerStep::GetCurrentVerStep()
	{
	}

	GetCurrentVerStep::~GetCurrentVerStep()
	{
	}

	int GetCurrentVerStep::Result() const
	{
		namespace fs = std::experimental::filesystem;
		const auto path = fs::current_path();
		auto filePath = path / "ResourcePack" / "ver.txt";

		FileListCreator fileListReader;
		const auto data = fileListReader.Create(filePath.string());
		return data.Version;
	}
}
#include "GetCurrentVer.h"
#include <filesystem>
#include "../Utility/FileTool.h"

namespace FileListMaker
{
	GetCurrentVer::GetCurrentVer()
	{
	}

	GetCurrentVer::~GetCurrentVer()
	{
	}

	int GetCurrentVer::Result() 
	{
		namespace fs = std::experimental::filesystem;
		const auto path = fs::current_path();
		auto filePath = path / "ResourcePack" / "NewestVer.txt";

		const auto data = _Parser.Parser(filePath.string());
		return data.Version;

		
	}
}

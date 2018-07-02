#include "ScanResourceFolder.h"
#include <filesystem>
#include <utility>
#include "../Utility/FileTool.h"


namespace PackingLogic
{
	ScanResourceFolder::ScanResourceFolder(std::string input_path)
		: _InputPath(std::move(input_path))
	{
	}

	Utility::FileList ScanResourceFolder::Make()
	{
		namespace fs = std::experimental::filesystem;
		for (auto& p : fs::directory_iterator(_InputPath))
		{
			if (is_directory(p))
			{
				_InputPath = p.path().string();
				Make();
			}

			_AddToList(p.path());
		}

		return _FileList;
	}

	void ScanResourceFolder::_AddToList(const std::experimental::filesystem::path& path)
	{
		std::vector<char> buffer;
		FileTool::ReadFileToBuffer(path.string(), buffer);

		const auto md5 = FileTool::CreateMD5(buffer);

		if (!is_directory(path))
		{
			const auto filepath = path.relative_path().string();
			const auto c = Utility::FileData{md5, filepath};
			_FileList.push_back(c);
		}
	}
}

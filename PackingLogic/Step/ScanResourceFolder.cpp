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
		for (auto& p : directory_iterator(_InputPath))
		{
			if (is_directory(p) && !is_empty(p))
			{
				_InputPath = p.path().string();
				Make();
			}

			if (is_directory(p) && is_empty(p))
			{
				const auto path = p.path().string() += "/";
				_AddToList(path);
			}

			if (is_regular_file(p))
			{
				_AddToList(p.path().string());
			}
		}

		return _FileList;
	}

	void ScanResourceFolder::_AddToList(const std::string& path)
	{
		std::vector<char> buffer;
		FileTool::ReadFileToBuffer(path, buffer);

		const auto md5 = FileTool::CreateMD5(buffer);

		const auto c = Utility::FileData{md5, path};
		_FileList.push_back(c);
	}
}
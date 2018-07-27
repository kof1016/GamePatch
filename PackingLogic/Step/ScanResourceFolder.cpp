#include "ScanResourceFolder.h"
#include <filesystem>
#include <utility>
#include "../../Utility/File/FileTool.h"


namespace BZbee::Sandbox::GamePatch::PackingLogic::Step
{
	ScanResourceFolder::ScanResourceFolder(std::string input_path)
		: _InputPath(std::move(input_path))
	{
	}

	Utility::DataDefine::FileList ScanResourceFolder::Make()
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
		Utility::File::ReadFileToBuffer(path, buffer);

		const auto md5 = Utility::File::CreateMD5(buffer);

		const auto c = Utility::DataDefine::FileData{md5, path};
		_FileList.push_back(c);
	}
}
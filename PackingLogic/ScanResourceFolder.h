#pragma once
#include <string>
#include "../Utility/DataDefine.h"
#include <filesystem>

namespace PackingLogic
{
	class ScanResourceFolder final
	{
	public:
		ScanResourceFolder() = delete;
		~ScanResourceFolder() = default;
		ScanResourceFolder(std::string input_path);

		Utility::FileList Make();

	private:
		void _AddToList(const std::experimental::filesystem::path& path);
		std::string _InputPath;
		Utility::FileList _FileList;

		std::string _FolderName;
	};
}

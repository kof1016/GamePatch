#pragma once
#include <string>
#include "../../Utility/DataDefine.h"
#include <filesystem>

namespace bZbee::Sandbox::GamePatch::PackingLogic::Step
{
	class ScanResourceFolder final
	{
	public:
		ScanResourceFolder() = delete;
		~ScanResourceFolder() = default;
		ScanResourceFolder(std::string input_path);

		Utility::DataDefine::FileList Make();

	private:
		void _AddToList(const std::string& path);
		std::string _InputPath;
		Utility::DataDefine::FileList _FileList;

		std::string _FolderName;
	};
}

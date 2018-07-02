#include "CreateZip.h"
#include "../Utility/FileTool.h"

namespace fs = std::experimental::filesystem;

namespace PackingLogic
{
	CreateZip::CreateZip(std::string save_path, Utility::FileList content)
		: _SavePath(std::move(save_path))
		, _FileList(std::move(content))
	{
	}

	CreateZip::~CreateZip()
	{
	}

	void CreateZip::Start()
	{
		for(auto& d : _FileList)
		{
			fs::path sourcePath(d.Path);
			const auto targetFolder = _SavePath / sourcePath.parent_path(); // sourceFile.filename() returns "sourceFile.ext".

			FileTool::CreateDir(targetFolder);

			copy_file(sourcePath, targetFolder / sourcePath.filename(), fs::copy_options::overwrite_existing);
		}
	}
}

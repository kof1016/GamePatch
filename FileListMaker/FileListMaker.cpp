#include "FileListMaker.h"
#include <filesystem>
#include <cassert>
#include <utility>
#include "../Utility/FileTool.h"


namespace FileListMaker
{
	FileListMaker::FileListMaker(std::string input_path, std::string output_path)
		: _InputPath(std::move(input_path))
		, _OutputPath(std::move(output_path))

	{
	}

	DataDefine::FileList FileListMaker::Make()
	{
		_CreateDirectory();
		_ScanInputPath();
		return _NewFileList;
	}

	void FileListMaker::_CreateDirectory()
	{
		namespace fs = std::experimental::filesystem;
		fs::create_directories(_OutputPath);
	}

	void FileListMaker::_ScanInputPath()
	{
		namespace fs = std::experimental::filesystem;

		std::vector<char> buffer;
		for (auto& p : fs::directory_iterator(_InputPath))
		{
			auto& fp = p.path();

			FileTool::ReadFileToBuffer(fp.relative_path().string(), buffer);

			FileTool::CreateMD5(buffer);

			_NewFileList.Contents.emplace(_MD5, DataDefine::FileList::Content{ _MD5, fp.relative_path().string() });
		}
	}
}

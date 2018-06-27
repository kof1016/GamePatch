#include "CreateFileListToFile.h"
#include <filesystem>
#include <fstream>
#include "DataDefine.h"

namespace PackingLogic
{
	CreateFileListToFile::CreateFileListToFile(int ver, std::list<Utility::FileList::Content>& file_list)
		: _Ver(ver)
		, _FileList(file_list)
	{
	}

	CreateFileListToFile::~CreateFileListToFile()
	{
	}

	std::list<Utility::FileList::Content> CreateFileListToFile::Create()
	{
		auto _Path = PackingLogic::GetCurrentFileListPath(_Ver);

		_CheckDirExists();

		_CreateFile();

		return _FileList;
	}

	void CreateFileListToFile::_CheckDirExists()
	{
		namespace fs = std::experimental::filesystem;
		fs::path p(_Path);
		CreateDir(p.parent_path().string());
	}

	void CreateFileListToFile::_CreateFile()
	{
		std::ofstream outfile(_Path, std::ofstream::out); //write mode

		for (auto& c : _FileList)
		{
			outfile << c.StateSymbol << "|" << c.MD5 << "|" << c.Path << std::endl;
		}

		outfile.close();
	}
}

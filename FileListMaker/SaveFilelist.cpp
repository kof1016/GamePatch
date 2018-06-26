#include "SaveFileList.h"
#include <filesystem>
#include <fstream>

namespace PackingLogic
{
	SaveFileList::SaveFileList(int ver, std::list<DataDefine::FileList::Content>& file_list)
	{
		_Ver = ver;
		_FileList = file_list;
	}

	SaveFileList::~SaveFileList()
	{
	}

	bool SaveFileList::Save()
	{
		namespace fs = std::experimental::filesystem;
		const auto path = fs::current_path();
		auto folderPath = path / "ResourcePack" / ("ver" + std::to_string(_Ver));

		_Path = folderPath.string();

		return fs::create_directories(folderPath);
	}

	 void SaveFileList::_CreateFileList()
	 {
	 	const auto fileName = std::to_string(_Ver) + "filelist.txt";
	 	const std::experimental::filesystem::path p1(_Path);
	 	auto p2 = p1 / fileName;
	
	 	std::ofstream outfile(p2.string(), std::ofstream::out); //write mode
	
	 	for (auto& c : _FileList)
	 	{
	 		outfile << c.GetFileState()<< "|" << c.MD5 << "|" << c.Path << std::endl;
	 	}
	
	 	outfile.close();
	 }
}

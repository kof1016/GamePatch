#include "ScanResourcePath.h"
#include <filesystem>
#include "../Utility/FileTool.h"
#include "../Utility/md5.h"

namespace FileListMaker
{
	ScanResourcePath::ScanResourcePath(std::string& resource_path, DataDefine::FileList& current_file_list)
	{
		_ResourcePath = resource_path;
		_CurrentFileList = current_file_list;
	}


	ScanResourcePath::~ScanResourcePath()
	{
	}


	int ScanResourcePath::Result()
	{
		namespace fs = std::experimental::filesystem;

		for (auto& p : fs::directory_iterator(_ResourcePath))
		{
			auto& fp = p.path();

			FileTool::ReadFileToBuffer(fp.relative_path().string(), _Buffer);
			 _CreateMD5();

			//current no, res have = add
			const auto r = _CurrentFileList.Contents.find(_MD5);
			if(r == _CurrentFileList.Contents.end())
			{
				r->second.State = DataDefine::FileList::Content::ADD;
				r->second.bChecked = true;
			}
			else
			{
				
			}
			 
			//DataDefine::FileList::Content c{ _MD5, fp.relative_path().string(), DataDefine::FileList::Content::FileState::ADD};
			//_CurrentFileList.Contents.emplace(_MD5, c);
		}

		//_CreateFileList();
		return 1;
	}

	void ScanResourcePath::_CreateMD5()
	{
		MD5 md5;
		md5.update(_Buffer.data(), _Buffer.size());
		md5.finalize();
		_MD5 = md5.hexdigest();
	}

	void ScanResourcePath::_CreateFileList()
	{
		const auto fileName = "filelist_ver" + std::to_string(_Ver) + ".txt";
		//const std::experimental::filesystem::path p1(_OutputPath);
		const std::experimental::filesystem::path p1("");
		auto p2 = p1 / fileName;

		std::ofstream outfile(p2.string(), std::ofstream::out); //write mode

		outfile << "buildversion=" << _CurrentFileList.Version << std::endl;

		for (auto& c : _CurrentFileList.Contents)
		{
			outfile << c.first << "|" << c.second.Path << std::endl;
		}

		outfile.close();
	}
}

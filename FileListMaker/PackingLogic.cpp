#include "FileListMaker.h"
#include <filesystem>
#include <utility>
#include "../Utility/FileTool.h"


namespace FileListMaker
{
	 FileListMaker::FileListMaker(std::string input_path)
	 	: _InputPath(std::move(input_path))
	 {
	 }

	 DataDefine::FileList FileListMaker::Make()
	 {
	 	DataDefine::FileList fileList;
	 	std::vector<char> buffer;
 
	 	namespace fs = std::experimental::filesystem;
	 	for (auto& p : fs::directory_iterator(_InputPath))
	 	{
	 		auto& fp = p.path();
 
	 		FileTool::ReadFileToBuffer(fp.relative_path().string(), buffer);
 
	 		auto md5 = FileTool::CreateMD5(buffer);

			auto c = DataDefine::FileList::Content{ md5, fp.relative_path().string() };
	 		fileList.Contents.push_back(c);
	 	}
 
	 	return fileList;
	 }
}

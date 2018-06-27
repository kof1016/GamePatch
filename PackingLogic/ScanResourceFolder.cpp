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
	 	Utility::FileList fileList;
	 	std::vector<char> buffer;
 
	 	namespace fs = std::experimental::filesystem;
	 	for (auto& p : fs::directory_iterator(_InputPath))
	 	{
	 		auto& fp = p.path();
	 		
	 		FileTool::ReadFileToBuffer(fp.string(), buffer);

			const auto md5 = FileTool::CreateMD5(buffer);

			const auto c = Utility::FileList::Content{ md5, fp.relative_path().string() };
	 		fileList.Contents.push_back(c);
	 	}
 
	 	return fileList;
	 }
}

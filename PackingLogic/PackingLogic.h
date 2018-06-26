#pragma once
#include <string>
#include "../Utility/DataDefine.h"

namespace PackingLogic
{
	 class FileListMaker final
	 {
	 public:
	 	FileListMaker() = default;
	 	~FileListMaker() = default;
	 	FileListMaker(std::string input_path);
	 	
	 	DataDefine::FileList Make();
 
	 private:
	 	std::string _InputPath;
	 };
}

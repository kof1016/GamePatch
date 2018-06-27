#pragma once
#include <string>
#include "../Utility/DataDefine.h"

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
	 	std::string _InputPath;
	 };
}

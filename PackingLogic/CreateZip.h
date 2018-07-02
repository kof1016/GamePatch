#pragma once
#include "../Utility/DataDefine.h"
#include <list>

namespace PackingLogic
{
	class CreateZip
	{
	public:
		CreateZip(std::string save_path, Utility::FileList content);
		~CreateZip();
		void Start();
	
	private:
		std::string _SavePath;
		Utility::FileList _FileList;
		
	};
}

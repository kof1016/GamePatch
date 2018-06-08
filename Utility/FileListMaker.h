#pragma once
#include "DataDefine.h"

namespace Utility
{
	class FileListMaker final
	{
	public:
		FileListMaker() = default;
		FileListMaker(const std::string& path, int version);
		~FileListMaker();

	private:
		void _GetAllFile(const std::string& path);
		void _ReadFile(const std::string&& relative_path);
		void _CreateMD5();
		void _WriteFile();

		std::vector<unsigned char> _Buffer;
		std::string _MD5;
		DataDefine::FileListData _FileListData;
	};

}
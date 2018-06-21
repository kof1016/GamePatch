#pragma once
#include <string>
#include <vector>
#include "../Utility/DataDefine.h"

namespace FileListMaker
{
	

	class FileListMaker final
	{
	public:
		FileListMaker() = default;
		FileListMaker(std::string input_path, std::string output_path, int version);
		void _CreateDirectory();
		~FileListMaker() = default;

	private:
		void _ComparisonLastVer();
		void _ScanInputPath();
		void _ReadFile(const std::string&& relative_path);
		void _CreateMD5();
		void _CreateFileList();

		std::vector<unsigned char> _Buffer;
		std::string _MD5;
		DataDefine::FileListData _FileListData;
		std::string _InputPath;
		std::string _OutputPath;
		int _Version;
	};

}

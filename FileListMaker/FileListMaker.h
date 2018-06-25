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
		FileListMaker(std::string input_path, std::string output_path);
		DataDefine::FileList Make();
		void _CreateDirectory();
		~FileListMaker() = default;

	private:
		void _ComparisonLastVer();
		void _ScanInputPath();

		std::string _MD5;
		DataDefine::FileList _NewFileList;
		std::string _InputPath;
		std::string _OutputPath;
		int _Version;
	};

}

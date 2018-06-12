#pragma once
#include <cstdio>
#include <string>

namespace Utility
{
	class FileWriter final
	{
	public:
		FileWriter(std::string file_name);
		~FileWriter();
		void OpenFile();
		void CloseFile() const;
		void Write(char* buffer, size_t nmemb) const;
	
	private:
		FILE* _File{nullptr};
		std::string _FileName;
	};
}

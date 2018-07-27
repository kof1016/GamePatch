#pragma once
#include <cstdio>
#include <string>

namespace BZbee::Sandbox::GamePatch::Utility::File
{
	class FileWriter final
	{
	public:
		FileWriter() = delete;
		FileWriter(std::string save_path, std::string mode);
		~FileWriter();

		void OpenFile();
		void CloseFile() const;
		void Write(char* buffer, size_t nmemb) const;
		void Write(const char* buffer, size_t nmemb) const;

	private:

		FILE* _File{nullptr};
		std::string _SavePath;
		std::string _Mode;
	};
}

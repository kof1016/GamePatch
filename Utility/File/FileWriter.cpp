#include "FileWriter.h"


namespace Utility
{
	FileWriter::FileWriter(std::string save_path, std::string mode)
	:_SavePath(std::move(save_path))
	,_Mode(std::move(mode))
	{
	}

	FileWriter::~FileWriter()
	{
		_File = nullptr;
	}

	void FileWriter::OpenFile()
	{
		//std::ofstream outfile("NewestVer.txt");
		fopen_s(&_File, _SavePath.data(), _Mode.data());
	}

	void FileWriter::CloseFile() const
	{
		fclose(_File);
	}

	void FileWriter::Write(char* buffer, size_t nmemb) const
	{
		fwrite(buffer, 1, nmemb, _File);
	}

	void FileWriter::Write(const char* buffer, size_t nmemb) const
	{
		fwrite(buffer, 1, nmemb, _File);
	}
}

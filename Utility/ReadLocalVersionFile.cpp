#include "ReadLocalVersionFile.h"


namespace Utility
{
	ReadLocalVersionFile::ReadLocalVersionFile(IReadable* read, const std::string path)
	{
		_Reader = read;
	}


	ReadLocalVersionFile::~ReadLocalVersionFile()
	{
	}

	auto ReadLocalVersionFile::GetCurrectVersion() const
	{
		{ return _Version; }
	}
}

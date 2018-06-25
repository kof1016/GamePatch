#include "CreateNewestVerDoc.h"
#include <fstream>
#include <string>

namespace FileListMaker
{
	CreateNewestVerDoc::CreateNewestVerDoc(int ver)
	{
		_Ver = ver+1;
	}

	CreateNewestVerDoc::~CreateNewestVerDoc()
	{
	}

	bool CreateNewestVerDoc::Result()
	{
		const auto write = "ver=" + std::to_string(_Ver);

		std::ofstream outfile("NewestVer.txt");
		if(!outfile.is_open())
		{
			return false;
		}

		outfile << write;
		outfile.close();
		return true;
	}
}

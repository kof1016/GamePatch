#include "VersionUpdater.h"
#include "GetCurrentVer.h"
#include <fstream>


namespace PackingLogic
{

	VersionUpdater::VersionUpdater()
	{
	}


	VersionUpdater::~VersionUpdater()
	{
	}

	int VersionUpdater::Update()
	{
		GetCurrentVer getCurrentVer;
		auto ver = getCurrentVer.Result();
		ver = ver + 1;
		
		const auto write = "ver=" + std::to_string(ver);

		std::ofstream outfile("NewestVer.txt");
		if (!outfile.is_open())
		{
			return -1;
		}

		outfile << write;
		outfile.close();

		return ver;
	}
}

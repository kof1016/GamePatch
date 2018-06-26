#pragma once

#include "../Utility/FileListParser.h"

namespace FileListMaker
{
	class GetCurrentVer final
	{
	public:
		GetCurrentVer();
		~GetCurrentVer();
		int Result();
	private:
		Utility::FileListParser _Parser;
	};
}

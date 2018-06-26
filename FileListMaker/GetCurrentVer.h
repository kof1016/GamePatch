#pragma once

#include "../Utility/FileListParser.h"

namespace PackingLogic
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

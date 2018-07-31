#include "VersionUpdater.h"

namespace bZbee::Sandbox::GamePatch::PackingLogic::Step
{
	VersionUpdater::VersionUpdater(int current_ver)
		: _NewtVer(current_ver + 1)
	{
	}


	VersionUpdater::~VersionUpdater()
	{
	}

	int VersionUpdater::UpdateVer()
	{
		return _NewtVer;
	}
}

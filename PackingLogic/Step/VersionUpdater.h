#pragma once
namespace bZbee::Sandbox::GamePatch::PackingLogic::Step
{
	class VersionUpdater
	{
	public:
		VersionUpdater() = delete;
		VersionUpdater(int current_ver);
		~VersionUpdater();
		int UpdateVer();
	private:
		int _NewtVer;
	};
}

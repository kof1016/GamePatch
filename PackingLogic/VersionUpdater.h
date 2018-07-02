#pragma once
namespace PackingLogic
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

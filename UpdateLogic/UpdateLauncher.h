#pragma once
#include "../Utility/StateMachine/StateMachine.h"
#include "../Utility/HttpDownload/DownloadProvider.h"
#include <map>
#include "../Utility/DataDefine.h"

namespace BZbee::Sandbox::GamePatch::UpdateLogic::Launcher
{
	class UpdateLauncher final
	{
	public:
		UpdateLauncher();
		~UpdateLauncher();
		void Start();
		void OnDownloadProgress(Utility::DataDefine::OnProgress&& callback);
		void OnUpdateSuccessEvent(Utility::DataDefine::OnSuccess&& callback);
		void OnNotNeedEvent(Utility::DataDefine::OnNotNeed&& callback);
	
	private:
		void _ToDownloadNewestVer();
		void _ToDownloadFileState();
		void _ToUnZip();
		void _ToMerge(const Utility::DataDefine::FileList& file_list, const path& file_path);
		void _ToParserFileListState(const path& file_path);
		void _ToDiffVerNumberState(int local_ver, int newest_ver);
		void _ToParserVerNumberState(path file_path);
		void _ToUpdteLocalVer();
		void _RemoveDownloadPack();

		Utility::DataDefine::OnProgress _OnProgress;
		Utility::DataDefine::OnSuccess _OnSuccess;
		Utility::DataDefine::OnNotNeed _OnNotNeed;

		Utility::HttpDownload::DownloadProvider _DownloadProvider;
		std::queue<path> _DownloadList;
		std::map<int, path> _FilePaths;
	};
}

#pragma once
#include "../Utility/StateMachine/StateMachine.h"
#include "../Utility/HttpDownload/DownloadProvider.h"
#include <map>
#include "../Utility/DataDefine.h"

namespace UpdateLogic
{
	class UpdateLauncher final
	{
	public:
		UpdateLauncher();
		~UpdateLauncher();
		void Start();
		void OnDownloadProgress(Utility::OnProgress&& callback);
		void OnUpdateSuccessEvent(Utility::OnSuccess&& callback);
		void OnNotNeedEvent(Utility::OnNotNeed&& callback);
	
	private:
		void _ToDownloadNewestVer();
		void _ToDownloadFileState();
		void _ToUnZip();
		void _ToMerge(const Utility::FileList& file_list, const path& file_path);
		void _ToParserFileListState(const path& file_path);
		void _ToDiffVerNumberState(int local_ver, int newest_ver);
		void _ToParserVerNumberState(path file_path);
		void _ToUpdteLocalVer();
		void _RemoveDownloadPack();
		
		Utility::OnProgress _OnProgress;
		Utility::OnSuccess _OnSuccess;
		Utility::OnNotNeed _OnNotNeed;
		
		Utility::DownloadProvider _DownloadProvider;
		std::queue<path> _DownloadList;
		std::map<int, path> _FilePaths;
	};
}

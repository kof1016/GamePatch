#pragma once
#include "../Utility/StateMachine.h"
#include "../Utility/DownloadProvider.h"
#include <map>

namespace UpdateLogic
{
	class UpdateLauncher final
	{
	public:
		UpdateLauncher();
		~UpdateLauncher();
		void Start();
		void Update();
		void Shutdown();
		void OnDownloadProgress(Utility::OnProgress&& callback);
		void OnUpdateSuccessEvent(Utility::OnSuccess&& callback);
		void OnNotNeedEvent(Utility::OnNotNeed&& callback);
	private:
		void _ToDownloadNewestVer();
		void _ToDownloadFileState();
		void _ToUnZip();
		void _ToMerge(const Utility::FileList& file_list, const path& file_path);
		void _ToParserFileListState(const path& file_path);
		void _ToDiffVerNumberState();
		void _ToParserVerNumberState(path file_path);
		
		void _ToUpdteLocalVer();
		void _RemoveDownloadPack();
		
		//Utility::StateMachine _StateMachine;
		Utility::OnProgress _OnProgress;
		Utility::OnSuccess _OnSuccess;
		Utility::OnNotNeed _OnNotNeed;
		
		Utility::DownloadProvider _DownloadProvider;
		std::queue<path> _DownloadList;
		std::map<int, path> _FilePaths;

		int _NewestVer{0};
		int _LocalVer{ 0 };
	};
}

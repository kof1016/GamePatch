#pragma once
#include "../Utility/StateMachine.h"
#include "../Utility/DownloadProvider.h"

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
		void _ToMerge(Utility::FileList file_list, path file_path);
		void _ToUpdteLocalVer();
		void _ToParserFilelistState(path file_path);
		void _ToDiffVerNumberState();
		
		void _ToParserVerNumberState(path file_path);
		
		//Utility::StateMachine _StateMachine;
		Utility::OnProgress _OnProgress;
		Utility::OnSuccess _OnSuccess;
		Utility::OnNotNeed _OnNotNeed;
		
		Utility::DownloadProvider _DownloadProvider;
		std::queue<path> _FilePaths;
		std::queue<path> _FilePathTmp;

		int _NewestVer{0};
		int _LocalVer{ 0 };
	};
}

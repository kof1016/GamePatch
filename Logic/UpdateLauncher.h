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
		void _ToDownloadFileState();
		void _ToParserFilelistState();
		void _ToGetDiffState(const Utility::FileList& local, const Utility::FileList& remote);
		void _ToDownloadDiffFileState();
		void _ToMoveFile() const;
		
		Utility::StateMachine _StateMachine;
		Utility::OnProgress _OnProgress;
		Utility::OnSuccess _OnSuccess;
		Utility::OnNotNeed _OnNotNeed;
		
		Utility::DownloadProvider _DownloadProvider;
		std::queue<std::string> _FilePaths;
	};
}

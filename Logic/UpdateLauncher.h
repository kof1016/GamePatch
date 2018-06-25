#pragma once
#include "../Utility/StateMachine.h"
#include "../Utility/DownloadProvider.h"

namespace Logic
{
	class UpdateLauncher final
	{
	public:
		UpdateLauncher();
		~UpdateLauncher();
		void Start();
		void Update();
		void Shutdown();
		void OnDownloadProgress(DataDefine::OnProgress&& callback);
		void OnUpdateSuccessEvent(DataDefine::OnSuccess&& callback);
		void OnNotNeedEvent(DataDefine::OnNotNeed&& callback);
	private:
		void _ToDownloadFileState();
		void _ToParserFilelistState();
		void _ToGetDiffState(const DataDefine::FileList& local, const DataDefine::FileList& remote);
		void _ToDownloadDiffFileState();
		void _ToMoveFile() const;
		
		Utility::StateMachine _StateMachine;
		DataDefine::OnProgress _OnProgress;
		DataDefine::OnSuccess _OnSuccess;
		DataDefine::OnNotNeed _OnNotNeed;
		
		Utility::DownloadProvider _DownloadProvider;
		std::queue<std::string> _FilePaths;
	};
}

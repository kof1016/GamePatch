#pragma once
#include "../Utility/StateMachine.h"
#include "ParserFilelistState.h"
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
	private:
		void _ToDownloadFileState();
		void _ToParserFilelistState();
		void _ToGetDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote);
		void _ToDownloadDiffFileState(DataDefine::FileListData::ShareContent contents);
		void _ToMoveFile();
		Utility::StateMachine _StateMachine;

		DataDefine::OnProgress _OnProgress;
		Utility::DownloadProvider _DownloadProvider;
	};
}



#pragma once
#include "../Utility/StateMachine.h"
#include "ParserFilelistState.h"

namespace Logic
{
	class UpdateLauncher final
	{
	public:
		UpdateLauncher();
		~UpdateLauncher();
		void Start();
		void Update();
	private:
		void _ToGetRemoteFileState();
		void _ToCompareFileState();
		void _ToFindDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote);
		Utility::StateMachine _StateMachine;
	};
}

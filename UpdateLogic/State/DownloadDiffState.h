#pragma once

#include "../../Utility/DataDefine.h"
#include "../../Utility/StateMachine/IState.h"

namespace bZbee::Sandbox::GamePatch::DownloadLogic::State
{
	class DownloadDiffState final : public Utility::StateMachine::IState
	{
	public:
		typedef std::function<void()> OnDone;
		DownloadDiffState(Utility::DataDefine::FileList file_list);
		~DownloadDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);
	private:
		Utility::DataDefine::FileList _FileList;
		OnDone _OnDone;
	};

}

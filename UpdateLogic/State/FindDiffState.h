#pragma once
#include "../../Utility/StateMachine/IState.h"
#include "../../Utility/DataDefine.h"
#include <queue>

namespace bZbee::Sandbox::GamePatch::DownloadLogic::State
{
	class FindDiffState final : public Utility::StateMachine::IState
	{
	public:
		typedef std::function<void(std::queue<std::string>)> OnDone;
		FindDiffState(Utility::DataDefine::FileList& local, Utility::DataDefine::FileList& remote);
		~FindDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);

	private:
		Utility::DataDefine::FileList _Local;
		Utility::DataDefine::FileList _Remote;
		OnDone _OnDone;
	};
}

#pragma once

#include "../../Utility/DataDefine.h"
#include "../../Utility/StateMachine/IState.h"

namespace UpdateLogic 
{
	class DownloadDiffState final : public Utility::IState
	{
	public:
		typedef std::function<void()> OnDone;
		DownloadDiffState(Utility::FileList file_list);
		~DownloadDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);
	private:
		Utility::FileList _FileList;
		OnDone _OnDone;
	};

}

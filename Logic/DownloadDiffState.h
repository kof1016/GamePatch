#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace UpdateLogic 
{
	class DownloadDiffState final : public Utility::IState
	{
	public:
		typedef std::function<void()> OnDone;
		DownloadDiffState(DataDefine::FileList::Content contents);
		~DownloadDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);
	private:
		DataDefine::FileList::Content _Contents;
		OnDone _OnDone;
	};

}

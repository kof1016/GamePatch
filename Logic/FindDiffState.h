#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace Logic
{
	class FindDiffState final : public Utility::IState
	{
	public:
		typedef std::function<void(DataDefine::FileListData::ShareContent)> OnDone;
		FindDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote);
		~FindDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);
	private:
		DataDefine::ShareFileList _Local;
		DataDefine::ShareFileList _Remote;
		
		OnDone _OnDone;

	};
}

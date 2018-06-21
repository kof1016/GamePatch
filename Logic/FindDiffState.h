#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"
#include <queue>

namespace Logic
{
	class FindDiffState final : public Utility::IState
	{
	public:
		typedef std::function<void(std::queue<std::string>)> OnDone;
		FindDiffState(const DataDefine::FileListData& local, const DataDefine::FileListData& remote);
		~FindDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);

	private:
		DataDefine::FileListData _Local;
		DataDefine::FileListData _Remote;
		OnDone _OnDone;
	};
}

#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"
#include <queue>

namespace UpdateLogic
{
	class FindDiffState final : public Utility::IState
	{
	public:
		typedef std::function<void(std::queue<std::string>)> OnDone;
		FindDiffState(const DataDefine::FileList& local, const DataDefine::FileList& remote);
		~FindDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(OnDone&& callback);

	private:
		DataDefine::FileList _Local;
		DataDefine::FileList _Remote;
		OnDone _OnDone;
	};
}

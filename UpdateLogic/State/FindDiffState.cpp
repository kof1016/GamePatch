#include "FindDiffState.h"
#include <utility>

namespace BZbee::Sandbox::GamePatch::UpdateLogic::State
{
	FindDiffState::FindDiffState(Utility::DataDefine::FileList& local, Utility::DataDefine::FileList& remote)
		:_Local(std::move(local)),
		_Remote(std::move(remote))
	{
	}

	FindDiffState::~FindDiffState()
	{
	}

	void FindDiffState::Enter()
	{
		// Utility::FileData::FilelistContent diffs;
  //
		// for (auto& e : _Remote.Contents)
		// {
		// 	const auto r = _Local.Contents.find(e.first);
		// 	
		// 	if (r == _Local.Contents.end())
		// 	{
		// 		diffs.insert(e);
		// 	}
		// }
  //
		// std::queue<std::string> paths;
  //
		// for(auto& e :diffs)
		// {
		// 	paths.emplace(e.second.Path);
		// }
  //
		// _OnDone(paths);
	}

	void FindDiffState::Leave()
	{
	}

	void FindDiffState::Update()
	{
	}

	void FindDiffState::OnDoneEvent(OnDone&& callback)
	{
		_OnDone = callback;
	}
}

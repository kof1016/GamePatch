#include "ParserFilelistState.h"
#include "../../Utility/DataDefine.h"



namespace BZbee::Sandbox::GamePatch::UpdateLogic::State
{
	ParserFilelistState::ParserFilelistState()
	{
	}


	ParserFilelistState::~ParserFilelistState()
	{
	}


	void ParserFilelistState::Enter()
	{
  //
	//	 auto local = reader.Create(LOCAL_FILELIST_PATH);
  //
		// auto remote = reader.Create(REMOTE_FILELIST_PATH);
  //
		// if (local.Version != remote.Version)
		// {
		// 	_OnDoneEvent(local, remote);
		// }
		// else
		// {
		// 	_OnFailEvent();
		// }
	}

	void ParserFilelistState::Leave()
	{
	}

	void ParserFilelistState::Update()
	{
	}

	void ParserFilelistState::OnDoneEvent(DoneEvent&& callback)
	{
		_OnDoneEvent = callback;
	}

	void ParserFilelistState::OnFailEvent(FailEvent&& callback)
	{
		_OnFailEvent = callback;
	}
}

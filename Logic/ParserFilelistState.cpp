#include "ParserFilelistState.h"
#include <memory>
#include "DataDefine.h"



namespace Logic
{
	ParserFilelistState::ParserFilelistState()
	{
	}


	ParserFilelistState::~ParserFilelistState()
	{
	}


	void ParserFilelistState::Enter()
	{
		// Utility::FileListReader reader;
  //
		// auto local = reader.ReadFile(LOCAL_FILELIST_PATH);
  //
		// auto remote = reader.ReadFile(REMOTE_FILELIST_PATH);
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

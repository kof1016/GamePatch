#include "ParserFilelistState.h"
#include "../Utility/FileReader.h"
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
		Utility::FileReader reader;

		auto local = reader.ReadFile(LOCAL_FILELIST_PATH);

		auto remote = reader.ReadFile(REMOTE_FILELIST_PATH);

		if (local.Version != remote.Version)
		{
			const DataDefine::ShareFileList localData(&local);
			const DataDefine::ShareFileList remoteData(&remote);
			_OnDoneEvent(localData, remoteData);
		}
		else
		{
			//_OnDoneEvent(localData, remoteData);
		}
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
}

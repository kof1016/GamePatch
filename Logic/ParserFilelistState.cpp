#include "ParserFilelistState.h"
#include "../Utility/FileReader.h"
#include <memory>


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

		auto local = reader.ReadFile(R"(..\resources\local-filelist.txt)");

		auto remote = reader.ReadFile(R"(..\resources\remote-filelist.txt)");

		// const std::shared_ptr<DataDefine::FileListData> localData(&local);
		// const std::shared_ptr<DataDefine::FileListData> remoteData(&remote);
  //
		// _OnDone(localData, remoteData);
	}

	void ParserFilelistState::Leave()
	{
	}

	void ParserFilelistState::Update()
	{
	}

	void ParserFilelistState::DoneEvent(OnCheckVersion&& callback)
	{
		_OnDone = callback;
	}
}

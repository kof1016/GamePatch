#include "ReceiveDone.h"

namespace BZbee::Sandbox::GamePatch::Utility::Receive
{
	ReceiveDone::ReceiveDone()
	{
		_OnDownloadDone = [](bool) {};
	}


	ReceiveDone::~ReceiveDone()
	{
	}

	void ReceiveDone::Bind(DataDefine::OnReceiveDownloadDone&& callback)
	{
		_OnDownloadDone = callback;

		if (_Have)
		{
			_OnDownloadDone(_Result);
		}
	}

	void ReceiveDone::Invoke(bool result)
	{
		_Have = true;
		_Result = result;
		_OnDownloadDone(result);
	}
}
#include "ReceiveDone.h"

namespace Utility
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
			callback(_Result);
		}
	}

	void ReceiveDone::Invoke(bool result)
	{
		_Have = true;
		_Result = result;
		_OnDownloadDone(result);
	}
}
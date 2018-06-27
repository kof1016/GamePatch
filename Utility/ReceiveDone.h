#pragma once
#include "DataDefine.h"


namespace Utility
{
	class ReceiveDone final
	{
	public:
		ReceiveDone();
		~ReceiveDone();
		void Bind(OnReceiveDownloadDone&& callback);
		void Invoke(bool result);
	
	private:
		OnReceiveDownloadDone _OnDownloadDone;
		bool _Result{ false };
		bool _Have{ false };
	};
}

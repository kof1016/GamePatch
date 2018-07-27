#pragma once
#include "../DataDefine.h"


namespace BZbee::Sandbox::GamePatch::Utility::Receive
{
	class ReceiveDone final
	{
	public:
		ReceiveDone();
		~ReceiveDone();
		void Bind(DataDefine::OnReceiveDownloadDone&& callback);
		void Invoke(bool result);
	
	private:
		DataDefine::OnReceiveDownloadDone _OnDownloadDone;
		bool _Result{ false };
		bool _Have{ false };
	};
}

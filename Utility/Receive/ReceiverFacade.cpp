#include "ReceiverFacade.h"

namespace bZbee::Sandbox::GamePatch::Utility::Receive
{
	ReceiverFacade::ReceiverFacade()
	{
	}

	ReceiverFacade::~ReceiverFacade()
	{
	}

	void ReceiverFacade::BindReceiverDone(DataDefine::OnReceiveDownloadDone&& callback)
	{
		_ReceiveDone.Bind(std::move(callback));
	}
	
	void ReceiverFacade::InvokeDownloadDone(bool result)
	{
		_ReceiveDone.Invoke(result);
	}

	void ReceiverFacade::BindWriteData(DataDefine::OnWriteData&& callback)
	{
		_ReceiveWriteData.Bind(std::move(callback));
	}

	void ReceiverFacade::InvokeWriteData(char* buffer, size_t total)
	{
		_ReceiveWriteData.Invoke(buffer, total);
	}

	void ReceiverFacade::BindProgress(DataDefine::OnProgress&& callback)
	{
		_ReceiveProgress.Bind(std::move(callback));
	}

	void ReceiverFacade::InvokeProgress(int total_size, int downloaded_size)
	{
		_ReceiveProgress.Invoke(total_size, downloaded_size);
	}
}

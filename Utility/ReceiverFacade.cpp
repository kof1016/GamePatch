#include "ReceiverFacade.h"

namespace Utility
{
	ReceiverFacade::ReceiverFacade()
	{
	}

	ReceiverFacade::~ReceiverFacade()
	{
	}

	void ReceiverFacade::BindReceiverDone(OnReceiveDownloadDone&& callback)
	{
		_ReceiveDone.Bind(std::move(callback));
	}
	
	void ReceiverFacade::InvokeDownloadDone(bool result)
	{
		_ReceiveDone.Invoke(result);
	}

	void ReceiverFacade::BindWriteData(OnWriteData&& callback)
	{
		_ReceiveWriteData.Bind(std::move(callback));
	}

	void ReceiverFacade::InvokeWriteData(char* buffer, size_t total)
	{
		_ReceiveWriteData.Invoke(buffer, total);
	}

	void ReceiverFacade::BindProgress(OnProgress&& callback)
	{
		_ReceiveProgress.Bind(std::move(callback));
	}

	void ReceiverFacade::InvokeProgress(int total_size, int downloaded_size)
	{
		_ReceiveProgress.Invoke(total_size, downloaded_size);
	}
}

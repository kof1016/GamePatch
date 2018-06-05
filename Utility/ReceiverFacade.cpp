#include "ReceiverFacade.h"

namespace Utility
{
	ReceiverFacade::ReceiverFacade()
	{
	}

	ReceiverFacade::~ReceiverFacade()
	{
	}

	void ReceiverFacade::bindReceiverDone(DataDefine::OnReceiveDownloadDone&& callback)
	{
		_ReceiveDone.Bind(std::move(callback));
	}
	
	void ReceiverFacade::InvokeDownloadDone(bool result)
	{
		_ReceiveDone.Invoke(result);
	}

	size_t ReceiverFacade::bindWriteData(DataDefine::OnWriteData&& callback)
	{
		return _ReceiveWriteData.Bind(std::move(callback));
	}

	size_t ReceiverFacade::InvokeWriteData(char* buffer, size_t size, size_t nmemb)
	{
		return _ReceiveWriteData.Invoke(buffer, size, nmemb);
	}

	void ReceiverFacade::bindProgresser(DataDefine::OnProgresser&& callback)
	{
		_ReceiveProgress.Bind(std::move(callback));
	}

	int ReceiverFacade::InvokeProgress(int total_size, int downloaded_size)
	{
		return _ReceiveProgress.Invoke(total_size, downloaded_size);
	}
}

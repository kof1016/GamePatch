#include "ProgressAdapter.h"


namespace Utility
{
	ProgressAdapter::ProgressAdapter()
	{
		
	}

	ProgressAdapter::~ProgressAdapter()
	{
		
	}

	void ProgressAdapter::Bind(DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
	}

	void ProgressAdapter::Invoke(int total_size, int downloaded_size) const
	{
		_OnProgress(total_size, downloaded_size);
	}

	int ProgressAdapter::CurlCallback(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow)
	{
		const auto adapter = reinterpret_cast<ProgressAdapter*>(buffer);
		adapter->Invoke(int(t), int(d));

		return 0;
	}
}

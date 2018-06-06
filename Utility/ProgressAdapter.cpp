#include "CurlProgressAdapter.h"


namespace Utility
{
	CurlProgressAdapter::CurlProgressAdapter()
	{
		
	}

	CurlProgressAdapter::~CurlProgressAdapter()
	{
		
	}

	void CurlProgressAdapter::Bind(DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
	}

	void CurlProgressAdapter::Invoke(int total_size, int downloaded_size) const
	{
		_OnProgress(total_size, downloaded_size);
	}

	int CurlProgressAdapter::CurlCallback(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow)
	{
		const auto adapter = reinterpret_cast<CurlProgressAdapter*>(buffer);
		adapter->Invoke(int(t), int(d));

		return 0;
	}
}

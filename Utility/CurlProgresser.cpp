#include "CurlProgresser.h"


namespace Utility
{
	CurlProgresser::CurlProgresser()
	{
		
	}

	CurlProgresser::~CurlProgresser()
	{
		
	}

	void CurlProgresser::bindCallback(DataDefine::OnProgresser&& callback)
	{
		_OnProgresser = callback;
	}

	int CurlProgresser::SendProgresser(int total_size, int downloaded_size) const
	{
		return _OnProgresser(total_size, downloaded_size);
	}

	int CurlProgresser::ProgressFunction(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow)
	{
		const auto call = reinterpret_cast<CurlProgresser*>(buffer);
		auto r =  call->SendProgresser(int(t), int(d));

		return 0;
	}
}

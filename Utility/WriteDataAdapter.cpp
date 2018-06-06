#include "CurlWriteDataAdapter.h"

namespace Utility
{
	CurlWriteDataAdapter::CurlWriteDataAdapter()
	{
	}

	CurlWriteDataAdapter::~CurlWriteDataAdapter()
	{
	}

	void CurlWriteDataAdapter::Bind(DataDefine::OnWriteData&& callback)
	{
		_OnWriteData = callback;
	}

	void CurlWriteDataAdapter::Invoke(char* buffer, size_t nmemb) const
	{
 		_OnWriteData(buffer, nmemb);
	}

	size_t CurlWriteDataAdapter::CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata)
	{
		const auto adapter = reinterpret_cast<CurlWriteDataAdapter*>(userdata);
		adapter->Invoke(buffer, nmemb);
		
		return nmemb;
	}
}

#include "CurlWriteDataAdapter.h"

namespace Utility
{
	CurlWriteDataAdapter::CurlWriteDataAdapter()
	{
	}

	CurlWriteDataAdapter::~CurlWriteDataAdapter()
	{
	}

	void CurlWriteDataAdapter::bindCallback(DataDefine::OnWriteData&& callback)
	{
		_OnWriteData = callback;
	}

	void CurlWriteDataAdapter::WriteData(char* buffer, size_t nmemb) const
	{
 		_OnWriteData(buffer, nmemb);
	}

	size_t CurlWriteDataAdapter::WriteFunction(char* buffer, size_t size, size_t nmemb, void* userdata)
	{
		const auto call = reinterpret_cast<CurlWriteDataAdapter*>(userdata);
		call->WriteData(buffer, nmemb);
		return nmemb;
	}
}

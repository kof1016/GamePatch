#include "WriteDataAdapter.h"

namespace Utility
{
	WriteDataAdapter::WriteDataAdapter()
	{
	}

	WriteDataAdapter::~WriteDataAdapter()
	{
	}

	void WriteDataAdapter::Bind(OnWriteData&& callback)
	{
		_OnWriteData = callback;
	}

	void WriteDataAdapter::Invoke(char* buffer, size_t nmemb) const
	{
 		_OnWriteData(buffer, nmemb);
	}

	size_t WriteDataAdapter::CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata)
	{
		const auto adapter = reinterpret_cast<WriteDataAdapter*>(userdata);
		adapter->Invoke(buffer, nmemb);
		
		return nmemb;
	}
}

#include "CurlDataWriter.h"

namespace Utility
{
	CurlDataWriter::CurlDataWriter()
	{
	}

	CurlDataWriter::~CurlDataWriter()
	{
	}

	void CurlDataWriter::bindCallback(DataDefine::OnWriteData&& callback)
	{
		_OnWriteData = callback;
	}

	size_t CurlDataWriter::WriteData(char* buffer, size_t size, size_t nmemb) const
	{
 		return _OnWriteData(buffer, size, nmemb);
	}

	size_t CurlDataWriter::WriteFunction(char* buffer, size_t size, size_t nmemb, void* userdata)
	{
		const auto call = reinterpret_cast<CurlDataWriter*>(userdata);
		call->WriteData(buffer, size, nmemb);
		return nmemb;
	}
}

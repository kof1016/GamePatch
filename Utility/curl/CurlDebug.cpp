#include "CurlDebug.h"
#include <string>

namespace Utility
{
	std::string CurlDebug::DebugInfo = "";

	CurlDebug::CurlDebug()
	{
	}


	CurlDebug::~CurlDebug()
	{
	}

	int CurlDebug::OnCallback(CURL* curl, curl_infotype ty, char* p, size_t len, void* puser)
	{
		auto psDebug = static_cast<std::string *>(puser);

		switch (ty)
		{
		case CURLINFO_HEADER_IN:
		case CURLINFO_HEADER_OUT:
		case CURLINFO_DATA_IN:
		case CURLINFO_DATA_OUT:
			psDebug->append(p, len);
			break;
		default:
			break;
		}
		return 0;
	}
}

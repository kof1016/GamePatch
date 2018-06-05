#pragma once

#include "../curl/curl.h"
#include <string>

namespace Utility
{
	class CurlDebug final
	{
	public:
		CurlDebug();
		~CurlDebug();
		static int OnCallback(CURL *curl, curl_infotype ty, char *p, size_t len, void *puser);
		static std::string DebugInfo;
	};

}

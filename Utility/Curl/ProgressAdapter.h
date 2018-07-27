#pragma once
#include "../DataDefine.h"
#include "curl/curl.h"
namespace BZbee::Sandbox::Patch::Utility::Curl
{
	class ProgressAdapter final
	{
	public:
		ProgressAdapter();
		~ProgressAdapter();

		static int CurlCallback(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow);

		void Bind(::Utility::OnProgress&& callback);
		void Invoke(int total_size, int downloaded_size) const;
				
	private:
		::Utility::OnProgress _OnProgress;
	};
}

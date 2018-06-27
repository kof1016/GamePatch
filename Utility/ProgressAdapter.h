#pragma once
#include "DataDefine.h"
#include "../curl/curl.h"
namespace Utility
{
	class ProgressAdapter final
	{
	public:
		ProgressAdapter();
		~ProgressAdapter();

		static int CurlCallback(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow);

		void Bind(OnProgress&& callback);
		void Invoke(int total_size, int downloaded_size) const;
				
	private:
		OnProgress _OnProgress;
	};
}

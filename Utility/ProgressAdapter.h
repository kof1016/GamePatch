#pragma once
#include "DataDefine.h"
#include "../curl/curl.h"
namespace Utility
{
	class CurlProgressAdapter final
	{
	public:
		CurlProgressAdapter();
		~CurlProgressAdapter();

		static int CurlCallback(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow);

		void Bind(DataDefine::OnProgress&& callback);
		void Invoke(int total_size, int downloaded_size) const;
				
	private:
		DataDefine::OnProgress _OnProgress;
	};
}

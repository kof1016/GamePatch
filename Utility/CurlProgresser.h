#pragma once
#include "DataDefine.h"
#include "../curl/curl.h"
namespace Utility
{
	class CurlProgresser
	{
	public:
		CurlProgresser();
		~CurlProgresser();
		void bindCallback(DataDefine::OnProgresser&& callback);
		
		static int ProgressFunction(void* buffer, curl_off_t t, curl_off_t d, curl_off_t ultotal, curl_off_t ulnow);
		
		int SendProgresser(int total_size, int downloaded_size) const;
				
	private:
		DataDefine::OnProgresser _OnProgresser;
	};
}

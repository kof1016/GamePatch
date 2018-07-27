#pragma once
#include "../DataDefine.h"

namespace BZbee::Sandbox::Patch::Utility::Curl
{
	class WriteDataAdapter final
	{
	public:
		WriteDataAdapter();
		~WriteDataAdapter();

		static size_t CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata);

		void Bind(::Utility::OnWriteData&& callback);
		void Invoke(char* buffer, size_t nmemb) const;

	private:
		::Utility::OnWriteData _OnWriteData;
	};
}
#pragma once
#include "../DataDefine.h"

namespace BZbee::Sandbox::GamePatch::Utility::Curl
{
	class WriteDataAdapter final
	{
	public:
		WriteDataAdapter();
		~WriteDataAdapter();

		static size_t CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata);

		void Bind(DataDefine::OnWriteData&& callback);
		void Invoke(char* buffer, size_t nmemb) const;

	private:
		DataDefine::OnWriteData _OnWriteData;
	};
}
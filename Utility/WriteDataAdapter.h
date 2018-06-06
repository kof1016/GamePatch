#pragma once
#include "DataDefine.h"

namespace Utility
{
	class CurlWriteDataAdapter final
	{
	public:
		CurlWriteDataAdapter();
		~CurlWriteDataAdapter();

		static size_t CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata);

		void Bind(DataDefine::OnWriteData&& callback);
		void Invoke(char* buffer, size_t nmemb) const;

	private:
		DataDefine::OnWriteData _OnWriteData;
	};
}
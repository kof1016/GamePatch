#pragma once
#include "DataDefine.h"

namespace Utility
{
	class CurlWriteDataAdapter final
	{
	public:
		CurlWriteDataAdapter();
		~CurlWriteDataAdapter();

		static size_t WriteFunction(char* buffer, size_t size, size_t nmemb, void* userdata);

		void WriteData(char* buffer, size_t nmemb) const;

		void bindCallback(DataDefine::OnWriteData&& callback);

	private:
		DataDefine::OnWriteData _OnWriteData;
	};
}
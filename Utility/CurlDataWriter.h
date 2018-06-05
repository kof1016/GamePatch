#pragma once
#include "DataDefine.h"

namespace Utility
{
	class CurlDataWriter final
	{
	public:
		CurlDataWriter();
		~CurlDataWriter();

		static size_t WriteFunction(char* buffer, size_t size, size_t nmemb, void* userdata);

		size_t WriteData(char* buffer, size_t size, size_t nmemb) const;

		void bindCallback(DataDefine::OnWriteData&& callback);

	private:
		DataDefine::OnWriteData _OnWriteData;
	};
}
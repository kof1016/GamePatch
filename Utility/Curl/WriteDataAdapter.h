#pragma once
#include "../DataDefine.h"

namespace Utility
{
	class WriteDataAdapter final
	{
	public:
		WriteDataAdapter();
		~WriteDataAdapter();

		static size_t CurlCallback(char* buffer, size_t size, size_t nmemb, void* userdata);

		void Bind(OnWriteData&& callback);
		void Invoke(char* buffer, size_t nmemb) const;

	private:
		OnWriteData _OnWriteData;
	};
}
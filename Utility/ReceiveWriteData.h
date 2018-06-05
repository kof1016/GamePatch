#pragma once
#include "DataDefine.h"
#include <vector>


namespace Utility
{
	class ReceiveWriteData final
	{
	public:
		ReceiveWriteData();
		~ReceiveWriteData();
		size_t Bind2(DataDefine::OnWriteData callback);

		size_t Bind(DataDefine::OnWriteData&& callback);
		size_t Invoke(char* buffer, size_t size, size_t nmemb);
	private:
		DataDefine::OnWriteData _OnWriteData;
		
		std::vector<char> _Temp;
	};
}

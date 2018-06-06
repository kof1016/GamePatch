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

		void Bind(DataDefine::OnWriteData&& callback);
		void Invoke(char* buffer, size_t total);
	private:
		DataDefine::OnWriteData _OnWriteData;
		
		std::vector<char> _Temp;
	};
}

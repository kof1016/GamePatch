#pragma once
#include "../DataDefine.h"
#include <vector>


namespace Utility
{
	class ReceiveWriteData final
	{
	public:
		ReceiveWriteData();
		~ReceiveWriteData();

		void Bind(OnWriteData&& callback);
		void Invoke(char* buffer, size_t total);
	private:
		OnWriteData _OnWriteData;
		
		std::vector<char> _Temp;
	};
}

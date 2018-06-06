#include "ReceiveWriteData.h"
#include <vector>


namespace Utility
{
	ReceiveWriteData::ReceiveWriteData()
	{
	}

	ReceiveWriteData::~ReceiveWriteData()
	{
	}

	void ReceiveWriteData::Bind(DataDefine::OnWriteData&& callback)
	{
		_OnWriteData = callback;

		if (!_Temp.empty())
		{
			_OnWriteData(_Temp.data(), _Temp.size());
		}
	}

	void ReceiveWriteData::Invoke(char* buffer, size_t total)
	{
		_Temp.clear();

		if (!_OnWriteData)
		{
			_Temp.insert(_Temp.end(), buffer, buffer + total);

		}
		else
		{
			_OnWriteData(buffer, total);
		}
	}
}

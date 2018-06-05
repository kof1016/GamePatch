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

	size_t ReceiveWriteData::Bind2(DataDefine::OnWriteData callback)
	{
		_OnWriteData = callback;

		if (!_Temp.empty())
		{
			return _OnWriteData(_Temp.data(), 1, _Temp.size());
		}

		return 0;
	}

	size_t ReceiveWriteData::Bind(DataDefine::OnWriteData&& callback)
	{
		_OnWriteData = callback;

		if (!_Temp.empty())
		{
			return _OnWriteData(_Temp.data(), 1, _Temp.size());
		}

		return 0;
	}

	size_t ReceiveWriteData::Invoke(char* buffer, size_t size, size_t nmemb)
	{
		_Temp.clear();
		auto value{0};

		if (!_OnWriteData)
		{
			_Temp.insert(_Temp.end(), buffer, buffer+nmemb);

			value = nmemb;
		}
		else
		{
			value = _OnWriteData(buffer, size, nmemb);
		}
		return value;
	}
}

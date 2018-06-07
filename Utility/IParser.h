#pragma once
#include "DataDefine.h"


namespace Utility
{
	class IParser
	{
	public:
		IParser()=default;
		virtual ~IParser() = default;
		virtual DataDefine::FileListData Load(const std::string& data) = 0;
	};
}
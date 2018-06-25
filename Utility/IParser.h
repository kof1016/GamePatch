#pragma once
#include "DataDefine.h"


namespace Utility
{
	class IParser
	{
	public:
		IParser()=default;
		virtual ~IParser() = default;
		virtual DataDefine::FileList Parser(const std::string& data) = 0;
	};
}
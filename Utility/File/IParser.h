#pragma once
#include "../DataDefine.h"


namespace bZbee::Sandbox::GamePatch::Utility::File
{
	class IParser
	{
	public:
		IParser()=default;
		virtual ~IParser() = default;
		virtual DataDefine::FileList Parser(const std::string& data) = 0;
	};
}
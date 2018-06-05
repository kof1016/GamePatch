#pragma once

namespace Utility
{
	class IReadable
	{
	public:
		virtual ~IReadable() = default;
		virtual void ReadFile() = 0;
	};
}

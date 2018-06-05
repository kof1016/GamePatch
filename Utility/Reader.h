#pragma once
#include "IReadable.h"

namespace Utility
{
	class Reader final : public IReadable
	{
	public:
		Reader();
		~Reader();
		void ReadFile() override;

	private:
	};

}

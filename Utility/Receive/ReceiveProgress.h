#pragma once
#include "../DataDefine.h"

namespace Utility
{
	class ReceiveProgress
	{
	public:
		ReceiveProgress();
		~ReceiveProgress();

		void Bind(OnProgress&& callback);
		void Invoke(int total_size, int downloaded_size);

	private:
		OnProgress _OnProgress;

		int _Total{0};
		int _Downloaded{0};
		bool _Have{false};
	};

}

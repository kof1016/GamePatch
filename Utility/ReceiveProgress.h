#pragma once
#include "ReceiveDone.h"

namespace Utility
{
	class ReceiveProgress
	{
	public:
		ReceiveProgress();
		~ReceiveProgress();

		void Bind(DataDefine::OnProgress&& callback);
		void Invoke(int total_size, int downloaded_size);

	private:
		DataDefine::OnProgress _OnProgress;

		int _Total{0};
		int _Downloaded{0};
		bool _Have{false};
	};

}

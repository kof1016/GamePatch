#pragma once
#include "ReceiveDone.h"

namespace Utility
{
	class ReceiveProgress
	{
	public:
		ReceiveProgress();
		~ReceiveProgress();

		void Bind(DataDefine::OnProgresser&& callback);
		int Invoke(int total_size, int downloaded_size);

	private:
		DataDefine::OnProgresser _OnProgresser;
	};

}

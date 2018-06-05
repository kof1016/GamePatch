#include "ReceiveProgress.h"

namespace Utility
{
	ReceiveProgress::ReceiveProgress()
	{
		_OnProgresser =
			[=](int total, int downloaded)
			{
				return 0;
			};
	}

	ReceiveProgress::~ReceiveProgress()
	{
	}

	void ReceiveProgress::Bind(DataDefine::OnProgresser&& callback)
	{
		_OnProgresser = callback;
	}

	int ReceiveProgress::Invoke(int total_size, int downloaded_size)
	{
		return _OnProgresser(total_size, downloaded_size);
	}
}

#include "ReceiveProgress.h"

namespace Utility
{
	ReceiveProgress::ReceiveProgress()
	{
		_OnProgress =
			[=](int total, int downloaded)
			{
				return 0;
			};
	}

	ReceiveProgress::~ReceiveProgress()
	{
	}

	void ReceiveProgress::Bind(DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
		
		if(_Have)
		{
			_OnProgress(_Total, _Downloaded);
		}
	}

	void ReceiveProgress::Invoke(int total_size, int downloaded_size)
	{
		_Total = total_size;
		_Downloaded = downloaded_size;
		_Have = true;
		_OnProgress(total_size, downloaded_size);
	}
}

#pragma once
#include <string>
#include <future>
#include "../Receive/ReceiverFacade.h"

namespace Utility
{
	class IDownloadable
	{
	public:
		virtual ~IDownloadable() = default;
		virtual std::shared_ptr<ReceiverFacade> Start(std::string url) = 0;
	};
}

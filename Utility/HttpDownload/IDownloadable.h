#pragma once
#include <string>
#include "ReceiverFacade.h"
#include <future>

namespace Utility
{
	class IDownloadable
	{
	public:
		virtual ~IDownloadable() = default;
		virtual std::shared_ptr<ReceiverFacade> Start(std::string url) = 0;
	};
}

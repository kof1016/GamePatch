#pragma once
#include <string>
#include <future>
#include "../Receive/ReceiverFacade.h"

namespace BZbee::Sandbox::GamePatch::Utility::HttpDownload
{
	class IDownloadable
	{
	public:
		virtual ~IDownloadable() = default;
		virtual std::shared_ptr<Receive::ReceiverFacade> Start(std::string url) = 0;
	};
}

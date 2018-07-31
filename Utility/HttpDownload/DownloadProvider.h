#pragma once
#include <list>
#include "IDownloadable.h"
#include <future>

namespace bZbee::Sandbox::GamePatch::Utility::HttpDownload
{
	class HttpDownloadTask;

	class DownloadProvider final : public IDownloadable
	{
	public:
		DownloadProvider();
		virtual ~DownloadProvider();

		std::shared_ptr<Receive::ReceiverFacade> Start(std::string url) override;

	private:
		std::list<HttpDownloadTask*> _Tasks;
	};
}

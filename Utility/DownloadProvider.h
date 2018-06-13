#pragma once
#include <list>
#include "IDownloadable.h"
#include <future>

namespace Utility
{
	class HttpDownloadTask;

	class DownloadProvider final : public IDownloadable
	{
	public:
		DownloadProvider();
		virtual ~DownloadProvider();

		std::shared_ptr<ReceiverFacade> Start(std::string url) override;

	private:
		std::list<HttpDownloadTask*> _Tasks;
	};
}

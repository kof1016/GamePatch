#pragma once
#include <list>
#include "IDownloadable.h"
#include <future>

namespace Utility
{
	class HttpDownloadTask;

	class HttpDownload final : public IDownloadable
	{
	public:
		HttpDownload();
		virtual ~HttpDownload();

		std::shared_ptr<ReceiverFacade> Start(std::string url) override;

	private:
		std::list<HttpDownloadTask*> _Tasks;
	};
}

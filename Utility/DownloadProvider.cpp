#include "DownloadProvider.h"
#include <thread>
#include "HttpDownloadTask.h"
#include <future>

namespace Utility
{
	//std::ofstream outfile;

	//std::FILE* fp;

	DownloadProvider::DownloadProvider()
	{
		//outfile.open("testfile.txt", std::ofstream::out | std::ofstream::app); //write mode | write data from eof 
		//outfile.clear();

		//outfile << std::endl;
		//outfile << buffer.data() << std::endl;
		//outfile << "dm5 = " << strmd5.data() << std::endl << std::endl;
	}

	DownloadProvider::~DownloadProvider()
	{
		int i = 0;
	}

	std::shared_ptr<ReceiverFacade> DownloadProvider::Start(std::string url)
	{
		const std::shared_ptr<ReceiverFacade> receiverFacade(new ReceiverFacade());

		auto task = new HttpDownloadTask(receiverFacade);
		_Tasks.emplace_back(task);

		task->BindDownloadDone
		(
			DataDefine::OnReceiveDownloadDone([=](bool result)
			{
				_Tasks.remove(task);
				delete task;
			})
		);

		std::thread t(&HttpDownloadTask::Connect, task, url);
		t.detach();

		return receiverFacade;
	}
}

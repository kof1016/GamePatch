#pragma once
#include "DataDefine.h"
#include "ReceiveDone.h"
#include "ReceiveWriteData.h"
#include "ReceiveProgress.h"

namespace Utility
{

	// template<typename T>
	// class Event
	// {
	// protected:
	// 	void Invoke()
	// 	{
	// 		
	// 	}
	// public:
	// 	void Add(T callback);
	// 	void Remove(T callback);
	// };

	class ReceiverFacade final
	{
	public:
		ReceiverFacade();
		~ReceiverFacade();

		void bindReceiverDone(DataDefine::OnReceiveDownloadDone&& callback);
		void InvokeDownloadDone(bool result);

		size_t bindWriteData(DataDefine::OnWriteData&& callback);
		size_t InvokeWriteData(char* buffer, size_t size, size_t nmemb);

		void bindProgresser(DataDefine::OnProgresser&& callback);
		int InvokeProgress(int total_size, int downloaded_size);

	private:
		ReceiveDone _ReceiveDone;
		ReceiveWriteData _ReceiveWriteData;
		ReceiveProgress _ReceiveProgress;
	};
}

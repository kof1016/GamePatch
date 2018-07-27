#pragma once
#include "../DataDefine.h"
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

		void BindReceiverDone(OnReceiveDownloadDone&& callback);
		void InvokeDownloadDone(bool result);

		void BindWriteData(OnWriteData&& callback);
		void InvokeWriteData(char* buffer, size_t total);

		void BindProgress(OnProgress&& callback);
		void InvokeProgress(int total_size, int downloaded_size);

	private:
		ReceiveDone _ReceiveDone;
		ReceiveWriteData _ReceiveWriteData;
		ReceiveProgress _ReceiveProgress;
	};
}

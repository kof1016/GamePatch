#pragma once

namespace FileListMaker
{
	class CreateNewestVerDoc
	{
	public:
		CreateNewestVerDoc(int ver);
		~CreateNewestVerDoc();
		bool Result();
	private:
		int _Ver;
	};
}
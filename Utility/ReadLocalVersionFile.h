#pragma once
#include <string>

namespace Utility
{
	class IReadable;

	class ReadLocalVersionFile
	{
	public:
		ReadLocalVersionFile(IReadable* read, std::string path);

		~ReadLocalVersionFile();

		auto GetCurrectVersion() const;

	private:
		IReadable* _Reader;
		std::string _Version{""};
	};
}

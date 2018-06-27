#include "MergeFileList.h"
#include "../Utility/cpplinq.hpp"

namespace PackingLogic
{
	MergeFileList::MergeFileList(Utility::FileList& current, Utility::FileList& all_source)
		: _Current(current)
		, _AllSource(all_source)
	{
	}


	MergeFileList::~MergeFileList()
	{
	}

	std::list<Utility::FileList::Content> MergeFileList::Result()
	{
		using namespace cpplinq;

		const auto current = from(_Current.Contents)
			>> select([](auto d) { return d.MD5; })
			>> to_list();

		const auto source = from(_AllSource.Contents)
			>> select([](auto d) { return d.MD5; })
			>> to_list();

		const auto remove = from(current)
			>> except(from(source))
			>> to_list();


		const auto add = from(source)
			>> except(from(current))
			>> to_list();

		auto result = from(add)
			>> select([&](auto md5)
			{
				const auto r = std::find_if(_AllSource.Contents.begin(), _AllSource.Contents.end(),
											[&](auto& d)
											{
												if (md5 == d.MD5)
												{
													d.StateSymbol = "+";
												}

												return md5 == d.MD5;
											});
				return *r;
			})
			>> to_list();

		auto result2 = from(remove)
			>> select([&](auto key)
			{
				const auto r = std::find_if(_Current.Contents.begin(), _Current.Contents.end(),
											[&](auto& d)
											{
												if (key == d.MD5)
												{
													d.StateSymbol = "-";
												}

												return key == d.MD5;
											});
				return *r;
			})
			>> to_list();

		result.insert(result.end(), result2.begin(), result2.end());

		return result;
	}
}

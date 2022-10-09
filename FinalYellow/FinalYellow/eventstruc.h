#pragma once

#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Events
{
public:
	void Add(const string& event);

	const vector<string>& GetAll() const;

	template<typename Predicate>
	int RemoveIf(Predicate predicate)
	{
		auto split_point = stable_partition(event_order_.begin(), event_order_.end(), predicate);
		int delEventsCount = split_point - event_order_.begin();

		for (auto i = event_order_.begin(); i != split_point; ++i)
		{
			events_.erase(*i);
		}
		event_order_.erase(event_order_.begin(), split_point);
		return delEventsCount;
	}

private:
	set<string> events_;
	vector<string> event_order_;
};

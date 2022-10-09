#pragma once
#include "date.h"
#include "eventstruc.h"

#include <map>
#include <iostream>
#include <vector>

using namespace std;

struct Entry
{
	Date date;
	string event;
};

ostream& operator << (ostream& os, const Entry& e);
bool operator == (const Entry& lhs, const Entry& rhs);

class Database
{
public:
	void Add(const Date& date, const string& event);

	template<typename Predicate>
	int RemoveIf(Predicate predicate)
	{
		int result = 0;
		for (auto& kv : data)
		{
			const Date& date = kv.first;
			result += kv.second.RemoveIf([=](const string& event) {
				return predicate(date, event);
		});
		}

		for (auto it = data.begin(); it != data.end();)
		{
			if (it->second.GetAll().empty())
			{
				data.erase(it++);
			} else
			{
				++it;
			}
		}
		return result;
	}

	template<typename Predicate>
	vector<Entry> FindIf(Predicate predicate) const
	{
		vector<Entry> result;
		for (const auto& x : data)
		{
			for (const auto& event : x.second.GetAll())
			{
				if(predicate(x.first, event))
				{
					result.push_back(Entry{ x.first, event });
				}
			}
		}
		return result;
	}

	void Print(ostream& os) const;

	Entry Last(const Date& date) const;

private:
	map<Date, Events> data;
};

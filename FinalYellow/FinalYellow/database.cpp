#include "database.h"

#include <algorithm>
#include <stdexcept>
#include <tuple>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
	data[date].Add(event);
}

void Database::Print(ostream& os) const
{
	for (const auto& x : data)
	{
		for (const auto event : x.second.GetAll())
		{
			os << x.first << ' ' << event << endl;
		}
	}
}

Entry Database::Last(const Date& date) const
{
	auto it = data.upper_bound(date);
	if (it == data.begin())
	{
		throw invalid_argument("");
	}
	--it;
	return{it->first, it->second.GetAll().back()};
}

ostream& operator << (ostream& os, const Entry& e)
{
	return os << e.date << " " << e.event;
}

bool operator == (const Entry& lhs, const Entry& rhs)
{
	return tie(lhs.date, lhs.event) == tie(rhs.date, rhs.event);
}


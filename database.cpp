#include "database.h"
#include <iostream>
#include <algorithm>
#include<map>
#include <set>
#include<string>
#include<vector>
#include <sstream>
#include <functional>

using namespace std;
ostream& operator<<(ostream& ost, const DateEvent& d_e)
{
	ost << setw(4) << setfill('0') << (d_e.date.year) << "-" << setw(2)
		<< setfill('0') << d_e.date.month << "-" << setw(2) << setfill('0') << d_e.date.day << " ";
	ost << d_e.ev;

	return ost;
}
ostringstream& operator<<(ostringstream& ost, const DateEvent& d_e)
{
	ost << setw(4) << setfill('0') << (d_e.date.year) << "-" << setw(2)
		<< setfill('0') << d_e.date.month << "-" << setw(2) << setfill('0') << d_e.date.day << " ";
	ost << d_e.ev;

	return ost;
}

void Database::Add(const Date& date, const string& event) 
{
	Date d(date.year, date.month, date.day);
	if (this->date_event[d].find(event) == this->date_event[d].end()) {
		this->date_event[d].insert(event);
		this->date_event_V[d].push_back(event);
	}
}
void Database::Print(ostream &c) const
{
	for (auto day : this->date_event_V)
	{
		for (auto ev : day.second)
		{
			c << setw(4) << setfill('0') << (day.first.year) << "-" << setw(2) 
				<< setfill('0') << day.first.month << "-" << setw(2) << setfill('0') << day.first.day << " " << ev << endl;
		}
	}
}
void Database::Print(ostringstream &c) const
{
	for (auto day : this->date_event_V)
	{
		for (auto ev : day.second)
		{
			c << setw(4) << setfill('0') << (day.first.year) << "-" << setw(2)
				<< setfill('0') << day.first.month << "-" << setw(2) << setfill('0') << day.first.day << " " << ev << endl;
		}
	}
}

DateEvent Database::Last(const Date& date) const {
	string last_event = ""; 
	if (date == Date{ 0,0,0 }) throw std::invalid_argument("No entries");;
	auto it = date_event_V.upper_bound(date);
	if (it != begin(date_event_V))
	{
		auto it2 = prev(it);
		if (!it2->second.empty())
		{
			return DateEvent({ it2->first, it2->second.back() });
		}
	}
	else throw invalid_argument("No");
	return DateEvent({Date(),""});

}



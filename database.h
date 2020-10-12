#pragma once
#include "date.h"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include "node.h"
#include <functional> 
#include <algorithm>    // std::stable_partition
#include <utility>
using namespace std;

struct DateEvent
{
	const Date date;
	const string ev;
};

class Database : public Date{
public:
	map<const Date, set<string>> date_event;
	map<const Date, vector<string>> date_event_V;


public:
	Database() = default;
	void Add(const Date& date, const string& event);
	void Print(ostream &c) const;
	void Print(ostringstream &c) const;
	DateEvent Last(const Date& date) const;
	template <typename Func>
	vector<DateEvent> FindIf(Func pred) const 
	{
		vector<DateEvent> res;
		for (const auto& d : this->date_event_V)
		{
			for (const auto& ev : d.second)
			{
				if (pred(d.first, ev))
				{
					res.push_back({ d.first , ev });
				}
			}
		}
		return res;
	}

	template <typename Func>
	int RemoveIf(const Func& pred)
		{
			int count = 0;

			map<const Date, vector<string>> new_date_event_V;
			map<const Date, set<string>> new_date_event;

			for (auto& d_ev : date_event_V)
			{
				const auto border = stable_partition(d_ev.second.begin(), d_ev.second.end(),
					[pred, d_ev](const auto& item)
				{
					return pred(d_ev.first, item);
				});

				const size_t tmp = d_ev.second.size();

				if (border == d_ev.second.end())
				{
					count += tmp;
				}
				else
				{
					new_date_event_V[d_ev.first] = vector<string>(border, d_ev.second.end());
					new_date_event[d_ev.first] = set<string>(border, d_ev.second.end());

					count += tmp - new_date_event_V.at(d_ev.first).size();
				}
			}

			date_event_V = new_date_event_V;
			date_event = new_date_event;

			return count;
		}
};
ostream& operator<< (ostream& ost, const DateEvent& de);
ostringstream& operator<< (ostringstream& ost, const DateEvent& de);
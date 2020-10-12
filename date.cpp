#include "date.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;


int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

Date ParseDate(istream& is) {
	// Реализуйте эту функцию
	stringstream date;
	int y, m, d;
	is >> y;
	is.get();
	is >> m;
	is.get();
	is >> d;
	Date d1(y, m, d);
	return d1;
}
const bool operator <(const Date& left, const Date& right)
{
	if (left.year== right.year) {
		if (left.month == right.month) {
			return left.day<right.day;
		}
		else return left.month<right.month;
	}
	else return left.year< right.year;
}

const bool operator >(const Date& left, const Date& right)
{
	if (left.year == right.year) {
		if (left.month == right.month) {
			return left.day>right.day;
		}
		else return left.month>right.month;
	}
	else return left.year>right.year;
}

const bool operator ==(const Date& left, const Date& right)
{
	if (left.year == right.year) {
		if (left.month == right.month) {
			return left.day == right.day;
		}
		else return false;
	}
	else return false;
}
const bool operator !=(const Date& left, const Date& right)
{
	return !(left == right);
}

bool operator<=(const Date &first, const Date &second) {
	return (first == second) || (first < second);
}
bool operator>=(const Date &first, const Date &second) {
	return (first == second) || (first > second);
}

ostream& operator<<(ostream& ost, const pair<const Date&, const vector<string>&> ev)
{

	for (auto e : ev.second)
	{
		ost << setw(4) << setfill('0') << (ev.first.year) << "-" << setw(2)
			<< setfill('0') << ev.first.month << "-" << setw(2) << setfill('0') << ev.first.day << " ";
	}
	return ost;
}
ostringstream& operator<<(ostringstream& ost, const pair<const Date&, const vector<string>&> ev)
{

	for (auto e : ev.second)
	{
		ost << setw(4) << setfill('0') << (ev.first.year) << "-" << setw(2)
			<< setfill('0') << ev.first.month << "-" << setw(2) << setfill('0') << ev.first.day << " ";
	}
	return ost;
}
ostream& operator<< (ostream& ost, const Date& date)
{

		ost << setw(4) << setfill('0') << (date.year) << "-" << setw(2)
			<< setfill('0') << date.month << "-" << setw(2) << setfill('0') << date.day;
	return ost;
}


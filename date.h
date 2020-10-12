#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;

class Date {
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int year, month, day;
	string event;
	Date(const Date & other) : year(other.GetYear()), month(other.GetMonth()), day(other.GetDay()) {}
	Date(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;
	}
	Date(int y, int m, int d, string ev)
	{
		year = y;
		month = m;
		day = d;
		event = ev;
	}
	Date() {
		year = 0;
		month = 0;
		day = 0;
	}
	Date(const string &stringDate) : year(0), month(0), day(0) {
		istringstream is = istringstream(stringDate);
		is >> year;
		is.get();
		is >> month;
		is.get();
		is >> day;
	}
	~Date() {}
	friend const bool operator <(const Date& left, const Date& right);
	friend const bool operator >(const Date& left, const Date& right);
	friend const bool operator ==(const Date& left, const Date& right);
	friend const bool operator !=(const Date& left, const Date& right);
	friend bool operator<=(const Date &, const Date &);
	friend bool operator>=(const Date &, const Date &);
};	
Date ParseDate(istream&);

	ostream& operator<< (ostream&, const Date&);
	ostream& operator<< (ostream& , const pair < const Date&, const vector<string>& >);
	ostringstream& operator<< (ostringstream& ost, const pair < const Date&, const vector<string>& > vec);

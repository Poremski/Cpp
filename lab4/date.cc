#include <ctime>  // time and localtime
#include "date.h"
#include <iomanip> // for setw and setfill

#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
using std::setw;
using std::setfill;
using std::string;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

//Date::Date(int y, int m, int d) {}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void Date::next() {
	if(++day > daysPerMonth[month-1])
	{
		day = 1;
		if(++month > 12){
			month = 1;
			++year;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	os << setw(4) << setfill('0') << d.getYear() << '-';
	os << setw(2) << setfill('0') << d.getMonth() << '-';
	os << setw(2) << setfill('0') << d.getDay();
	return os;
}



std::istream& operator>>(std::istream& is, Date& d)
{
	int year, month, day;
	string s;
	getline(is, s);
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

	try
	{
		size_t pos = s.find("-");
		year = stoi(s.substr(0,pos));
		s.erase(0, pos+1);

		pos = s.find("-");
		month = stoi(s.substr(0,pos));
		if(month < 1 || month > 12)
		{
			throw std::invalid_argument("Month must be between 1 and 12");
		}
		s.erase(0, pos+1);


		pos = s.find("-");
		day = stoi(s.substr(0,pos));
		if(day < 1 || day > Date::daysPerMonth[month-1])
		{
			throw std::invalid_argument("Day must be between 1 and maximum for month");
		}
		s.erase(0, pos+1);

		d = Date (year, month, day);
	} catch(std::exception& e)
	{
		//std::cout << typeid(e).name() << ": " << e.what() << std::endl;
		is.setstate (std::ios::failbit);
		d = Date (0, 0, 0);
	}
	

	return is;
}


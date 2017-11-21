#include "templates.h"
#include <string>
#include <iostream>
#include "date.h"

using std::string;
using Templates::string_cast;
using Templates::toString;
using std::cout;
using std::endl;

bool test_int()
{
	int a = string_cast<int>("12");
	int b = 12;

	if(a != b)
	{
		cout << "test_int: not equal (" + toString(a) + " != " + toString(b) + ")" << endl;
		return false;
	}

	cout << "test_int: PASSED" << endl;
	return true; 
}

bool test_double()
{
	double a = string_cast<double>("1.45");
	double b = 1.45;

	if(a != b)
	{
		cout << "test_double: not equal (" + toString(a) + " != " + toString(b) + ")" << endl;
		return false;
	}

	cout << "test_double: PASSED" << endl;
	return true; 
}

bool test_long()
{
	long a = string_cast<long>("111222");
	long b = 111222;

	if(a != b)
	{
		cout << "test_long: not equal (" + toString(a) + " != " + toString(b) + ")" << endl;
		return false;
	}

	cout << "test_long: PASSED" << endl;
	return true; 
}

bool test_date()
{
	Date a = string_cast<Date>("2017-04-30");
	Date b{2017,04,30};

	if(a != b)
	{
		cout << "test_date: not equal (" + toString(a) + " != " + toString(b) + ")" << endl;
		return false;
	}

	cout << "test_date: PASSED" << endl;
	return true; 
}

bool test_bool()
{
	bool a = string_cast<bool>("1");
	bool b = true;

	if(a != b)
	{
		cout << "test_bool: not equal (" + toString(a) + " != " + toString(b) + ")" << endl;
		return false;
	}

	cout << "test_bool: PASSED" << endl;
	return true; 
}
int main()
{
	std::cout << "== test_tostring ==================" << std::endl;
	bool a = test_int();
	bool b = test_double();
	bool c = test_long();
	bool d = test_date();
	bool e = test_bool();

	bool passed = a && b && c && d && e;
	if(passed) {
		std::cout << "-- All tests passed! --------------" << std::endl;
	} 
	std::cout << "===================================" << std::endl;
}
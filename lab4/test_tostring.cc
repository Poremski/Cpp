#include "templates.h"
#include "date.h"
#include <string>
#include <iostream>

using Templates::toString;
using std::string;
using std::cout;
using std::endl;

bool test_int()
{
	int a = 1;
	int b = 2;
	string res = toString(a) + " " + toString(b);

	if(res != "1 2")
	{
		cout << "test_int: strings not equal (" + res + " != 1 2)" << endl;
		return false;
	}

	cout << "test_int: PASSED" << endl;
	return true; 
}

bool test_double()
{
	double a = 1.43;
	double b = 3.14;
	string res = toString(a) + " " + toString(b);
	if(res != "1.43 3.14")
	{
		cout << "test_double: strings not equal (" + res + " != 1 2)" << endl;
		return false;
	}

	cout << "test_double: PASSED" << endl;
	return true; 
}

bool test_long()
{
	long a = 1234;
	long b = 5678;
	string res = toString(a) + " " + toString(b);
	if(res != "1234 5678")
	{
		cout << "test_long: strings not equal (" + res + " != 1234 5678)" << endl;
		return false;
	}

	cout << "test_long: PASSED" << endl;
	return true; 
}

bool test_longlong()
{
	long long a = 1234;
	long long b = 5678;
	string res = toString(a) + " " + toString(b);
	if(res != "1234 5678")
	{
		cout << "test_longlong: strings not equal" << endl;
		return false;
	}

	cout << "test_longlong: PASSED" << endl;
	return true; 
}

bool test_date()
{
	Date a{2017,10,11};
	Date b{2016,1,1};
	string res = toString(a) + " " + toString(b);
	if(res != "2017-10-11 2016-01-01")
	{
		cout << "test_date: strings not equal (" << res << " != 2017-10-11 2016-01-01" << endl;
		return false;
	}

	cout << "test_date: PASSED" << endl;
	return true; 
}

bool test_string()
{
	string a{"hejhej"};
	string b{"ettettett"};
	string res = toString(a) + " " + toString(b);
	if(res != "hejhej ettettett")
	{
		cout << "test_string: strings not equal (" << res << " != hejhej ettettett" << endl;
		return false;
	}

	cout << "test_string: PASSED" << endl;
	return true; 
}

bool test_bool()
{
	bool a{true};
	bool b{false};
	string res = toString(a) + " " + toString(b);
	if(res != "1 0")
	{
		cout << "test_bool: strings not equal (" << res << " != 1 0" << endl;
		return false;
	}

	cout << "test_bool: PASSED" << endl;
	return true; 
}

bool test_all()
{
	int a = 1;
	double b = 3.14;
	long c = 11111111;
	long long d = 111111111111;
	Date e{2017,10,11};
	string f{"hej hej"};
	bool g = true;
	string res = toString(a) + toString(b) + toString(c) + toString(d) + toString(e) + toString(f) + toString(g);

	if(res != "13.14111111111111111111112017-10-11hej hej1"){
		cout << "test_all: strings not equal" << endl;
		return false;
	}

	cout << "test_all: PASSED" << endl;
	return true; 
}

int main()
{
	std::cout << "== test_tostring ==================" << std::endl;
	bool a = test_int();
	bool b = test_double();
	bool c = test_long();
	bool d = test_longlong();
	bool e = test_date();
	bool f = test_string();
	bool g = test_bool();
	bool h = test_all();

	bool passed = a && b && c && d && e && f && g && h;
	if(passed) {
		std::cout << "-- All tests passed! --------------" << std::endl;
	}
	std::cout << "===================================" << std::endl;



}
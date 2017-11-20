#include <iostream>
#include <iomanip> // for setw and setfill
#include "date.h"
#include <sstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;





/*
 * Prints the date d in the format yyyy-mm-dd. You shall replace this
 * function with an overloaded operator<<, and add an overloaded operator>>.
 *
 */
void print(const Date& d, std::stringstream& out) {
	out << setw(4) << setfill('0') << d.getYear() << '-';
	out << setw(2) << setfill('0') << d.getMonth() << '-';
	out << setw(2) << setfill('0') << d.getDay();
	//cout << d << endl;
}

bool test_output()
{
	std::stringstream correct;
	//in.str("2017-11-20\n2017-10-11\n2017-11-21\n2017-10-12");
	std::stringstream out;
	Date d;
	Date d1{2017,10,11};
	print(d, correct); // för att få en sträng av dagens datum
	correct << '\n' << "2017-10-11";
	out << d << '\n' << d1;
	/*d.next();
	d1.next();
	out << d << '\n' << d1; */

	if(correct.str() != out.str())
	{
		cout << "test_basic: strings not equal" << endl;
		return false;
	}
	cout << "test_basic: PASSED" << endl;
	return true; 
}

bool test_next_simple()
{

	std::stringstream correct;
	std::stringstream out;
	Date d{2017, 10, 11};
	correct << "2017-10-11";
	out << d;
	d.next();
	correct << "\n2017-10-12";
	out << '\n' << d;

	if(correct.str() != out.str())
	{
		cout << "test_next_simple: strings not equal (" << d << " != 2017-10-12)" << endl;
		return false;
	}
	cout << "test_next_simple: PASSED" << endl;
	return true; 
}

bool test_next_month()
{
	std::stringstream correct;
	std::stringstream out;

	// Jan 31 - Feb 1
	Date d1{2017, 1, 31};
	correct << "2017-01-31";
	out << d1;
	d1.next();
	correct << "\n2017-02-01";
	out << '\n' << d1;

	if(correct.str() != out.str())
	{
		cout << "test_next_month: strings not equal (Jan 31 - Feb 1)" << endl;
		return false;
	}

	//clear streams
	correct.str("");
	correct.clear();
	out.str("");
	out.clear();

	// Feb 28 - Mar 1
	Date d2{2017, 2, 28};
	correct << "2017-02-28";
	out << d2;
	d2.next();
	correct << "\n2017-03-01";
	out << '\n' << d2;

	if(correct.str() != out.str())
	{
		cout << "test_next_month: strings not equal (Feb 28 - Mar 1)" << endl;
		return false;
	}

	cout << "test_next_month: PASSED" << endl;
	return true; 
}

bool test_next_year()
{
	std::stringstream correct;
	std::stringstream out;

	Date d{2017, 12, 31};
	correct << "2017-12-31";
	out << d;
	d.next();
	correct << "\n2018-01-01";
	out << '\n' << d;

	if(correct.str() != out.str())
	{
		cout << "test_next_year: strings not equal (" << d << " != 2018-01-01)" << endl;
		return false;
	}

	cout << "test_next_year: PASSED" << endl;
	return true; 
}

bool test_next_35_days()
{
	std::stringstream correct;
	std::stringstream out;
	Date d1{2017, 11, 30};
	correct << "2017-11-30";
	out << d1;
	for(int i = 0; i != 35; ++i)
	{
		d1.next();
	}
	correct << "\n2018-01-04";
	out << '\n' << d1;

	if(correct.str() != out.str())
	{
		cout << "test_next_35_days: strings not equal (" << d1 << " != 2018-01-04)" << endl;
		return false;
	}

	cout << "test_next_35_days: PASSED" << endl;
	return true;
}

bool test_input_basic()
{
	std::stringstream in;
	std::stringstream correct;
	std::stringstream out;
	Date d;
	in.str("2017-10-11");
	in >> d;
	out << d;
	correct << "2017-10-11";

	if(correct.str() != out.str())
	{
		cout << "test_input_basic: strings not equal (" << d << " != 2017-10-11)" << endl;
		return false;
	}

	cout << "test_input_basic: PASSED" << endl;
	return true;

}

bool test_input_spaces()
{
	std::stringstream in;
	std::stringstream correct;
	std::stringstream out;
	Date d;
	in.str("2017     -   10 -         11");
	in >> d;
	out << d;
	correct << "2017-10-11";

	if(correct.str() != out.str())
	{
		cout << "test_input_spaces: strings not equal (" << d << " != 2017-10-11)" << endl;
		return false;
	}

	cout << "test_input_spaces: PASSED" << endl;
	return true;

}

bool test_input_extra_dash()
{
	std::stringstream in;
	Date d;
	in.str("2017--10--11");
	in >> d;
	if(in.good())
	{
		cout << "test_input_extra_dash: failbit not set when it should" << endl;
		return false;
	}

	cout << "test_input_extra_dash: PASSED" << endl;
	return true;
}

bool test_input_invalid_data()
{
	std::stringstream in;
	Date d;
	in.str("2017-100-11");
	in >> d;
	if(in.good())
	{
		cout << "test_input_invalid_data: failbit not set when it should (month)" << endl;
		return false;
	}

	in.clear();
	in.str("2017-10-111");
	in >> d;
	if(in.good())
	{
		cout << "test_input_invalid_data: failbit not set when it should (day)" << endl;
		return false;
	}

	cout << "test_input_invalid_data: PASSED" << endl;
	return true;
}

int main() {
	//field_test();
	std::cout << "== date_test ======================" << std::endl;
	bool passed{true};
	bool a = test_output();
	bool b = test_next_simple();
	bool c = test_next_month();
	bool d = test_next_year();
	bool e = test_next_35_days();
	bool f = test_input_basic();
	bool g = test_input_spaces();
	bool h = test_input_extra_dash();
	bool i = test_input_invalid_data();

	passed = a && b && c && d && e && f && g && h && i;
	if(passed) {
		std::cout << "-- All tests passed! --------------" << std::endl;
	}
	std::cout << "===================================" << std::endl;
/*	std::stringstream in;
	std::stringstream out;
	// Check input and output of dates. Uncomment the following when you 
	// have added operator>> and operator<<.
	
	bool cont = true;
	while (cont) {
		out << "Type a date: ";
		Date aDate;
		in >> aDate;
		if (in.eof()) {
			cont = false;
		} else if (!cin.good()) {
			out << "Wrong input format" << endl;
			// restore stream state and ignore the rest of the line
			in.clear();
			in.ignore(10000, '\n');
		}
		else {
			out << "Output: " << aDate << endl;
		}
	}
	
	// Check 'next' by creating an object describing today's date, then
	// printing dates more than a month ahead
	out << "--- Today and more than a month ahead:" << endl;
	Date d1;
	print(d1, out);
	out << endl;
	for (int i = 1; i <= 35 ; ++i) {
		d1.next();
		print(d1, out);
		out << endl;
	}
	
	// Check so 'next' functions correctly from one year to the next
	out << "--- New Year's Eve and the next day:" << endl;
	Date d2(2013, 12, 31);
	print(d2, out);
	out << endl;
	d2.next();
	print(d2, out);
	out << endl;  */
}

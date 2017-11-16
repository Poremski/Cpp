#include "TagRemover.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

bool test(string fname)
{
	TagRemover tr("files/" + fname + ".html");
	tr.print("files/" + fname + "_result.txt");

	std::ifstream f1{"files/" + fname + "_correct.txt"};
	std::ifstream f2{"files/" + fname + "_result.txt"};

	char c1, c2;
	while((c1 = f1.get()) != EOF && (c2 = f2.get()) != EOF)
	{
		if(c1 != c2)
		{
			std::cout << fname << ": files not equal" << std::endl;
			return false;;
		}
	}
	if((c1 = f1.peek()) != EOF || (c2 = f2.peek()) != EOF)
	{
		std::cout << fname << ": files not equal" << std::endl;
		return false;

	}
	std::cout << fname << ": PASSED" << std::endl;
	return true;
}
int main()
{

	std::cout << "== test-tag-remover ===============" << std::endl;
	bool passed{true};
	bool a = test("test_tag_remove");
	bool b = test("test_spchar_replace");
	bool c = test("test_double_tag_remove");
	bool d = test("test_multiline_remove_tag");
	bool e = test("test");

	passed = a && b && c && d && e;
	if(passed) {
		std::cout << "-- All tests passed! --------------" << std::endl;
	}
	std::cout << "===================================" << std::endl;
}
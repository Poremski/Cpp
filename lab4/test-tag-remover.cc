#include "TagRemover.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

void test(string fname)
{
	TagRemover tr("files/" + fname + ".html");
	tr.print("files/" + fname + "_result.txt");

	std::ifstream f1{"files/" + fname + "_correct.txt"};
	std::ifstream f2{"files/" + fname + "_correct.txt"};

	char c1, c2;
	while((c1 = f1.get()) != EOF && (c2 = f2.get()) != EOF)
	{
		if(c1 != c2)
		{
			std::cout << fname << ": files not equal" << std::endl;
			return;
		}
	}
	if((f1.eof() && !f2.eof()) || (!f1.eof() && f2.eof()))
			std::cout << fname << ": files not equal" << std::endl;
}
int main()
{
	test("test_tag_remove");
	test("test_spchar_replace");
	test("test_double_tag_remove");
	test("test_multiline_remove_tag");
	test("test");
}
#include "primes.h"
#include <string>
#include <iostream>
#include <fstream>

using std::string;

bool test(string fname)
{
	Primes primes(35, "primesfiles/" + fname + "_result.txt");

	std::ifstream f1{"primesfiles/" + fname + "_correct.txt"};
	std::ifstream f2{"primesfiles/" + fname + "_result.txt"};

	char c1, c2;
	while((c1 = f1.get()) != EOF && (c2 = f2.get()) != EOF)
	{
		if(c1 != c2)
		{
			std::cout << fname << ": files not equal (" << c1 << " != " << c2 << " at pos " << f1.tellg() << std::endl;
			return false;;
		}
	}
	if((c1 = f1.peek()) != EOF || (c2 = f2.peek()) != EOF)
	{
		std::cout << fname << ": files not equal (both files not at EOF)" << std::endl;
		return false;

	}
	std::cout << fname << ": PASSED" << std::endl;
	return true;

}

int main()
{
	std::cout << "== test-tag-remover ===============" << std::endl;

	bool a = test("test_primes");

	bool passed = a;
	if(passed) {
		std::cout << "-- All tests passed! --------------" << std::endl;
	}
	std::cout << "===================================" << std::endl;
}
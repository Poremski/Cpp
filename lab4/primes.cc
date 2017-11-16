#include "primes.h"
#include <string>
#include <fstream>
using std::string;

Primes::Primes(int M, string fname)
{
	std::ofstream of{fname};

	of.put(' ');
}
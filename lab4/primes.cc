#include "primes.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using std::string;
using std::vector;

void print_primes(int m, string& primes)
{
	for(int i = 0; i != m+1; i++)
	{
		if(i == 10) std::cout << 1;
		else if(i == 20) std::cout << 2;
		else if(i == 30) std::cout << 3;
		else std::cout << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i != m+1; i++)
	{
		std::cout << i%10;
	}
	std::cout << std::endl;
	std::cout << primes << std::endl;
}

void findP(string s, int* p)
{
	for(size_t i = *p+1; i<s.size(); ++i)
	{
		if(s[i] == 'P')
		{
			*p = i;
			return;
		}
	}
}

string calc_primes(int m, std::ofstream* of)
{
	string primes (m+1, 'P');
	primes[0] = 'C';
	primes[1] = 'C';

	string outPrimes{primes};
	for(char c:primes)
	{
		of->put(c);
	}

	int p{2};
	while(p*2 <= m)
	{
		of->put('\n');	
		for(size_t i = p+1; i != primes.size(); i++)
		{
			int r = i%p;

			if(r == 0)
			{
				primes[i] = 'C';
			}
		}
		for(char c: primes)
		{
			of->put(c);
		}
		findP(primes, &p);
		}


	return primes;

}

void get_nbrs(vector<int>* v, string* primes)
{
	for(size_t i = 0; i != primes->size(); ++i)
	{
		if(primes->at(i) == 'P')
			v->push_back(i);
	}
}

Primes::Primes(int M, string fname)
{
	std::ofstream of{fname};
	string primes = calc_primes(M, &of);
	vector<int> v;
	get_nbrs(&v, &primes);
	of.put('\n');
	string temp;
	for(int n:v)
	{
		temp += std::to_string(n) + " ";
	}
	for(char c:temp)
	{
		of.put(c);
	}
}
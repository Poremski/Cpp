#include "TagRemover.h"
#include <string>
#include <istream>
#include <fstream>

using std::string;

TagRemover::TagRemover(string fname) 
{

}

void TagRemover::print(string fname) 
{
	std::ofstream of{fname};
	of.put(' ');
}
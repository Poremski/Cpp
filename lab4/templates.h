#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <string>
#include <sstream>

namespace Templates
{
	template<typename T>
	std::string toString(T& in)
	{
		std::stringstream rtrn;
		rtrn << in;
		return rtrn.str();
	}
}

#endif
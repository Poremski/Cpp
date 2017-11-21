#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

namespace Templates
{
	template<typename T>
	std::string toString(T& in)
	{
		std::stringstream rtrn;
		rtrn << in;
		return rtrn.str();
	}

	template<typename T>
	T string_cast(std::string s){
		std::istringstream in;
		in.str(s);
		T rtrn;
		try{
			in >> std::noskipws >> rtrn;
		} catch(std::exception& e)
		{
			std::string t = typeid(rtrn).name();
			throw std::invalid_argument("Can't cast from string to " + t);
		}
		return rtrn;
	}
}

#endif
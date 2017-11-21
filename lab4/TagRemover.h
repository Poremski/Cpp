#ifndef __TAGREMOVER_H
#define __TAGREMOVER_H

#include <string>


class TagRemover {
public:
	TagRemover(std::string);
	void print(std::string);
private: 
	std::string output;
};

#endif
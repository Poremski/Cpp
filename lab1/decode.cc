#include <coding.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

void decode_file(std::string filename)
{
	std::ifstream in{filename + ".dec"};

	std::string str{""};
	int c;
	while((c = in.get()) != EOF) {
        str += decode(char(c));
    }

    std::ofstream out{filename + ".enc"};

    out << str;
}

int main(int argc, const char** argv)
{
	if(argc != 2){
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
	}

	std::string name{argv[1]};

	decode_file(name);
}
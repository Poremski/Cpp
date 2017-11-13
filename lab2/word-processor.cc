#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::string to_lower(std::string s)
{
	int length = s.size();
	for(int i = 0; i<length; ++i)
	{
		s[i] = std::tolower(s[i]);
	}
	return s;
}

void process(std::string file)
{
	std::ifstream in(file);
	std::string line;

	std::ofstream out("words.txt");
	while(std::getline(in, line))
	{
		std::string str(line);
		int trigrams = line.size()-2;
		trigrams = (trigrams > 0)? trigrams:0;
		str += " " + std::to_string(trigrams);
		std::vector<std::string> v;
		for(int i = 0; i != trigrams; ++i)
		{
			std::string pushstr = line.substr(i, 3);
			v.push_back(to_lower(pushstr));
		}
		std::sort(v.begin(), v.end());
		for(std::string s:v)
		{
			str += " " + s;
		}
		out << str << std::endl;
	}
}

int main()
{
	std::string file = "/usr/share/dict/words";
	process(file);
}
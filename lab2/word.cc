#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "word.h"

using std::vector;
using std::string;

Word::Word(const string& w, const vector<string>& t): word{w}, trigrams{t} {}

string Word::get_word() const {
	return Word::word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	int count = 0;
	for(string s:t)
	{
		if(std::binary_search(Word::trigrams.begin(), Word::trigrams.end(), s)) count++;
	}
	return count;
}

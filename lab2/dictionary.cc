#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;

void add_trigram_suggestions(vector<string>& suggestions, const string& missWord)
{
	int size = missWord.size();
	int trigrams = size-2;
	if(trigrams > 1)
	{
		for(Word word : words)
		{
			if(word.get_matches(missWord) >= trigrams/2)
			{
				suggestions.push_back(word.get_word());
			}
		}
	}
	
}

Dictionary::Dictionary() {
	std::ifstream in("words.txt");
	std::string line;
	while(std::getline(in, line))
	{
		string row{line};

		// get word
		std::size_t pos = row.find(" ");
		string str = row.substr(0, pos);

		row.erase(0,pos+1);

		// get number
		pos = row.find(" ");
		int nbr_of_trigrams = std::stoi(row.substr(0, pos));
		row.erase(0,pos+1);

		vector<string> trigrams;

		// put trigrams is vector
		for(int i = 0; i != nbr_of_trigrams; ++i)
		{
			pos = row.find(" ");
			trigrams.push_back(row.substr(0,pos));
			row.erase(0, pos+1);
		}
		if(str.size() <= 25)
		{
			Word word(str, trigrams);
			Dictionary::words[str.size()].push_back(word);
			Dictionary::word_set.insert(str);
		}
	}
}

bool Dictionary::contains(const string& word) const {
	std::unordered_set<string>::const_iterator got = Dictionary::word_set.find(word);
	return got != Dictionary::word_set.end();
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	add_trigram_suggestions(suggestions, word);
	return suggestions;
}

int main()
{
	Dictionary dict;
}
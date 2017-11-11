#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;

void get_trigrams(vector<string>& trigrams, const string& word)
{
	if(word.size()-2 > 0)
	{
		for(int i = 0; i != word.size()-2; ++i)
		{
			trigrams.push_back(word.substr(i, 3));
		}
	}
} 

void Dictionary::rank_suggestions(vector<string>& suggestions, const string& missWord) const
{

}

void Dictionary::add_trigram_suggestions(vector<string>& suggestions, const string& missWord) const
{
	int size = missWord.size();
	vector<string> trigrams;
	//vector<Word::Word> relevantWords(Dictionary::words[size-1]);
	//relevantWords.insert(relevantWords.end(), Dictionary::words[size].begin(), Dictionary::words[size].end());
	//relevantWords.insert(relevantWords.end(), Dictionary::words[size+1].begin(), Dictionary::words[size+1].end());
	get_trigrams(trigrams, missWord);
	if(trigrams.size() != 0)
	{
		for(int i = -1; i != 2; ++i)
		{
			for(Word word : Dictionary::words[size+i])
			{
				if(word.get_matches(trigrams) >= trigrams.size() / 2) {
					suggestions.push_back(word.get_word());
					std::cout << word.get_word() << std::endl;	
				}
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
	Dictionary::add_trigram_suggestions(suggestions, word);
	Dictionary::rank_suggestions(suggestions, word);
	return suggestions;
}



int main()
{
	Dictionary dict;
	vector<string> vect(dict.get_suggestions("abbatil"));
	for(string s:vect)
	{
		std::cout << s << std::endl;
	}
}
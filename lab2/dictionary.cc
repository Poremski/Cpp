#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"
#include <math.h>
#include <utility>

using std::string;
using std::vector;

void get_trigrams(vector<string>& trigrams, const string& word)
{
	if(word.size()-2 > 0)
	{
		for(unsigned int i = 0; i != word.size()-2; ++i)
		{
			trigrams.push_back(word.substr(i, 3));
		}
	}
}

void Dictionary::rank_suggestions(vector<string>& suggestions, const string& missWord) const
{
	vector<std::pair<int, string>> bestWords;
	int d[26][26];

	for(int i = 0; i != 26; ++i)
	{
		d[i][0] = i;
		d[0][i] = i;
	}
	
	for(auto word : suggestions)
	{
		for(unsigned int i = 1; i != missWord.size()+1; ++i)
		{
			for(unsigned int j = 1; j != word.size()+1; ++j)
			{
				int min = (missWord[i-1] == word[j-1])? d[i-1][j-1]:  d[i-1][j-1] + 1;
				min = fmin(min, d[i-1][j] + 1);
				min = fmin(min, d[i][j-1] + 1);
				d[i][j] = min;
			}
		}

	std::pair<int, string> best(d[missWord.size()][word.size()] ,word);
	bestWords.push_back(best);
	}

	std::sort(bestWords.begin(), bestWords.end());
	suggestions.clear();
	for(auto p : bestWords)
	{
		suggestions.push_back(p.second);
	}
}

void Dictionary::add_trigram_suggestions(vector<string>& suggestions, const string& missWord) const
{
	int size = missWord.size();
	vector<string> trigrams;
	get_trigrams(trigrams, missWord);
	if(trigrams.size() != 0)
	{
		for(int i = -1; i != 2; ++i)
		{
			for(Word word : Dictionary::words[size+i])
			{
				if(word.get_matches(trigrams) >= trigrams.size() / 2) 
				{
					suggestions.push_back(word.get_word());
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

		if(str.size() <= 25)
		{
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
			Word word(str, trigrams);
			Dictionary::words[str.size()].push_back(word);
			Dictionary::word_set.insert(str);
		}
	}
	
}

bool Dictionary::contains(const string& word) const 
{
	std::unordered_set<string>::const_iterator got = Dictionary::word_set.find(word);
	return got != Dictionary::word_set.end();
}

vector<string> Dictionary::get_suggestions(const string& word) const 
{
	vector<string> suggestions;
	Dictionary::add_trigram_suggestions(suggestions, word);
	Dictionary::rank_suggestions(suggestions, word);
	suggestions.resize(5);
	return suggestions;
}
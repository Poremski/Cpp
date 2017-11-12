#include <string>
#include <vector>
#include <fstream>
#include <iostream>
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
		for(int i = 0; i != word.size()-2; ++i)
		{
			trigrams.push_back(word.substr(i, 3));
		}
	}
} 

void print_matrix(int d[26][26], int size){
	for(int i = 0; i<size; i++)
	{
		for(int j = 0; j<size; j++)
		{
			std::cout << d[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Dictionary::rank_suggestions(vector<string>& suggestions, const string& missWord) const
{
	vector<std::pair<int, string>> bestWords;
	int d[26][26];
	for(int i = 0; i < missWord.size(); ++i){
		for(int j = 0; j < missWord.size(); ++j){
			d[i][j] = 0;
		}
	}
	for(int i = 0; i < missWord.size(); ++i)
	{
		d[i][0] = i;
		d[0][i] = i;
	}

	for(string word : suggestions)
	{
		for(int i = 0; i < missWord.size(); ++i){
			for(int j = 0; j < missWord.size(); ++j){
				d[i][j] = 0;
			}
		}

		for(int i = 1; i <= missWord.size(); ++i)
		{
			for(int j = 1; j <= word.size(); ++j)
			{
				if(missWord[i] == word[j])
				{
					d[i][j] = d[i-1][j-1];
				} else {
					int d1 = d[i-1][j-1] + 1;
					int d2 = d[i-1][j] + 1;
					int d3 = d[i][j-1] + 1;
					int min = fmin(d1, d2);
					d[i][j] = fmin(min, d3);
				}
			}
		}

	std::pair<int, string> best(d[missWord.length()][word.length()] ,word);
	bestWords.push_back(best);
	//print_matrix(d, missWord.size());
	}
	std::sort(bestWords.begin(), bestWords.end());
	suggestions.clear();

	for(std::pair<int, string> p : bestWords)
	{
		suggestions.push_back(p.second);
		std::cout << p.first << ", " << p.second << std::endl;
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
				if(word.get_matches(trigrams) >= trigrams.size() / 2) {
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
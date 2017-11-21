#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "word.h"

class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
	void add_trigram_suggestions(std::vector<std::string>& suggestions, const std::string& missWord) const;
	void rank_suggestions(std::vector<std::string>& suggestions, const std::string& missWord) const;
private:
	const int max_length = 25;
	std::unordered_set<std::string> word_set;
	std::vector<Word> words[25];
};

#endif

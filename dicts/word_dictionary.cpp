#include "word_dictionary.hpp"
#include "dictionary.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using namespace std;


word_dictionary::word_dictionary(vector<string> word_list) : words(move(word_list)) {}


void word_dictionary::add_word(string word) { 
    this->words.push_back(move(word));
}


void word_dictionary::set_words(vector<string> word_list) { 
    this->words = move(word_list); 
}


void word_dictionary::val_append(string &pattern, uint32_t index) const { 
#ifdef _DEBUG
    pattern += this->words.at(index);
#else
    pattern += this->words[index];
#endif
}


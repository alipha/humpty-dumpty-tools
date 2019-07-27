#ifndef DICTS_WORD_DICTIONARY_HPP
#define DICTS_WORD_DICTIONARY_HPP

#include "dictionary.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using namespace std;


class word_dictionary : public dictionary {
public:
    word_dictionary() : words() {}
    word_dictionary(vector<string> word_list);
    
    void add_word(string word);
    void set_words(vector<string> word_list);
    
    void val_append(string &pattern, uint32_t index) const override;

    uint32_t combinations() const override { return this->words.size(); }
    
private:
    vector<string> words;
};

#endif

#ifndef DICTS_SINGLE_WORD_DICT_HPP
#define DICTS_SINGLE_WORD_DICT_HPP

#include "dictionary.hpp"
#include <cstdint>
#include <string>
#include <utility>

using namespace std;


class single_word_dict : public dictionary {
public:
    single_word_dict() : word() {}
    single_word_dict(string w) : word(move(w)) {}
    
    void add_char(char ch) { this->word += ch; }
	void set_word(string w) { this->word = move(w); }
    
    void val_append(string &pattern, uint32_t) const override { pattern += this->word; }
    uint32_t combinations() const override { return 1; }
    
private:
    string word;
};

#endif

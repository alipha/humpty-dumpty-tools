#include "set_dictionary.hpp"
#include "dictionary.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>

using namespace std;


set_dictionary::set_dictionary() : chars(), sub_dicts(), combos(0) {}


void set_dictionary::set_dictionary::add_char(char ch) {
    this->chars += ch;
    this->combos++;
}


void set_dictionary::add_sub_dict(shared_ptr<const dictionary> dict) {
    this->sub_dicts[this->dict_combinations()] = move(dict);
    this->combos += dict->combinations();
}


void set_dictionary::val_append(string &pattern, uint32_t index) const {
    uint32_t dict_combos = this->dict_combinations();

    if(index >= dict_combos) {
#ifdef _DEBUG
        pattern += this->chars.at(index - dict_combos);
#else
        pattern += this->chars[index - dict_combos];
#endif
    }

    auto it = this->sub_dicts.upper_bound(index);
    it--;
    it->second->val_append(pattern, index - it->first);
}

uint32_t set_dictionary::dict_combinations() const {
    return this->combos - this->chars.length();
}

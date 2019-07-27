#ifndef DICTS_SET_DICTIONARY_HPP
#define DICTS_SET_DICTIONARY_HPP

#include "dictionary.hpp"
#include <cstddef>
#include <map>
#include <memory>
#include <string>

using namespace std;


class set_dictionary : public dictionary {
public:
    set_dictionary();
    
    void add_char(char ch);
    void add_sub_dict(shared_ptr<const dictionary> dict);
    
    void val_append(string &pattern, uint32_t index) const override;
    uint32_t combinations() const override { return this->combos; }
    
private:
    uint32_t dict_combinations() const;
    
    string chars;
    map<uint32_t, shared_ptr<const dictionary>> sub_dicts;
    uint32_t combos;
};

#endif

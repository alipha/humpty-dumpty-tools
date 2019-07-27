#ifndef DICTS_WORD_TRANSFORM_DICT_HPP
#define DICTS_WORD_TRANSFORM_DICT_HPP

#include "dictionary.hpp"
#include "../transform_type.hpp"
#include <cstdint>
#include <string>

using namespace std;

class selector;
class word_dictionary;


class word_transform_dict : public dictionary {
public:
    word_transform_dict();
    word_transform_dict(const word_dictionary *word_dictionary, int transforms);

    void set_word_dict(const word_dictionary *word_dictionary);
    void set_transform_types(int transforms);

    void sel_append(string &pattern, selector &s) const override;
    void val_append(string &pattern, uint32_t index) const override;
    uint32_t combinations() const override { return this->combos; }
    
private:
    void compute_combinations();
    
    transform_type select_transform(selector &s) const;
    string transform(const string &value, transform_type selected_transform) const;

    const word_dictionary *word_dict;
    int transform_types;
    uint32_t combos;
};

#endif

#ifndef DICTS_PATTERN_DICTIONARY_HPP
#define DICTS_PATTERN_DICTIONARY_HPP

#include "dictionary.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <map>
#include <string>

using namespace boost::multiprecision;
using namespace std;

class selector;


class pattern_dictionary : public dictionary {
public:
    pattern_dictionary();
    pattern_dictionary(vector<string> &&pattern_list);

    void add_pattern(string pat);
    void set_patterns(vector<string> &&pattern_list);

    void sel_append(string &pat, selector &s) const override;
    void val_append(string &pat, uint32_t index) const override;
    uint32_t combinations() const override;

    uint128_t exact_combinations() const { return this->combos; }

private:
    map<uint128_t, string> patterns;
    uint128_t combos;
};

#endif

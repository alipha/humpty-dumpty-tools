#include "pattern_dictionary.hpp"
#include "../pattern.hpp"
#include "../selector.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace boost::multiprecision;
using namespace std;


pattern_dictionary::pattern_dictionary() : patterns(), combos(0) {}


pattern_dictionary::pattern_dictionary(vector<string> &&pattern_list) {
    this->set_patterns(move(pattern_list));
}


void pattern_dictionary::add_pattern(string pat) {
    /*pattern p = pattern_parser::parse(pat);

    patterns[combinations] = move(pat);
    combinations += p.get_combinations();*/
}


void pattern_dictionary::set_patterns(vector<string> &&pattern_list) {
    this->patterns.clear();
    this->combos = 0;

    for(auto &&pattern : pattern_list)
        this->add_pattern(pattern);
}


void pattern_dictionary::sel_append(string &pat, selector &s) const {
    
}


void pattern_dictionary::val_append(string &pat, uint32_t index) const {
    throw logic_error("pattern_dictionary::val_append is not implemented.");
}


uint32_t pattern_dictionary::combinations() const {
    throw logic_error("pattern_dictionary::get_combinations is not implemented.");
}


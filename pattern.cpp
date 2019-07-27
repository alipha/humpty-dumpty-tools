#include "pattern.hpp"
#include "selector.hpp"
#include "dicts/dictionary.hpp"
#include <numeric>
#include <string>


string pattern::get(selector &s) const {
    string result;

    for(auto &part : this->parts) {
        part.sel_append(result, s);
    }

    return result;
}


double pattern::combinations() const {
    if(this->combos != 0.0) {
        return this->combos;
    }

    for(auto &part : this->parts) {
        this->combos += part.combinations();
    }

    return this->combos;
}



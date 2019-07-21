#include "pattern.hpp"
#include "selector.hpp"
#include "dictionary.hpp"
#include <numeric>
#include <string>


string pattern::get(selector &s) const {
    string result;

    for(auto &part : parts) {
        result += *part.get(s);
    }

    return result;
}


double pattern::get_combinations() const {
    if(combinations != 0.0) {
        return combinations;
    }

    for(auto &part : parts) {
        combinations += part.get_combinations();
    }

    return combinations;
}



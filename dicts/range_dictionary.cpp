#include "range_dictionary.hpp"
#include "dictionary.hpp"
#include <boost/format.hpp>
#include <cstdint>
#include <string>
#include <stdexcept>

using namespace std;


void range_dictionary::set_range(char first_ch, char last_ch) {
    if(last_ch > first_ch)
        throw invalid_argument(boost::str(boost::format("char %1% must be < char %2%") % first_ch % last_ch));

    this->first = first_ch;
    this->last = last_ch;
}


void range_dictionary::val_append(string &pattern, uint32_t index) const { 
    pattern += static_cast<char>(static_cast<uint32_t>(this->first) + index); 
}


uint32_t range_dictionary::combinations() const { 
    return static_cast<uint32_t>(this->last - this->first + 1);
}


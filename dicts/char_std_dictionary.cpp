#include "char_std_dictionary.hpp"
#if _DEBUG
#include <boost/format.hpp>
#include <stdexcept>
#endif
#include <cstdint>
#include <cstring>
#include <string>

using namespace std;


char_std_dictionary::char_std_dictionary(const char *char_list) : chars(char_list), len(strlen(char_list)) {}


void char_std_dictionary::set_chars(const char *char_list) {
    this->chars = char_list;
    this->len = strlen(char_list);
}


void char_std_dictionary::val_append(string &pattern, uint32_t index) const { 
#ifdef _DEBUG
    if(index >= len)
        throw out_of_range(boost::str(boost::format("char_std_dictionary.val_append called with index %1% >= %2%") % index % this->len));
#endif
    pattern += this->chars[index]; 
}


#include "pattern_parser.hpp"
#include "dicts/standard_dictionary.hpp"
#include <cstddef>
#include <string>
#include <stdexcept>


using namespace std;


pattern_parser::pattern_parser() {
    standard_dictionary::init();
}


pattern pattern_parser::parse(const string &input) const {
    string segment;
/*
    for(string::const_iterator it = input.begin(); it != input.end(); ++it) {
        if(*it == '\\') {
            ++it;
            if(it == input.end())
                throw new invalid_argument();
        } else if(*it == '[') {

        } else {
            segment += *it;
        }
    }*/

    return pattern();
}

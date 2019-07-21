#include "pattern_parser.hpp"
#include "standard_dictionary.hpp"
#include <string>


using namespace std;
using namespace boost;


pattern_parser::pattern_parser() {
    standard_dictionary::init();
}


pattern pattern_parser::parse(const string &input) const {
    return pattern();
}

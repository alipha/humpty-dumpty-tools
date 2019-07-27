#include "standard_dictionary.hpp"
#include "char_std_dictionary.hpp"
#include "../transform_type.hpp"

#include <boost/format.hpp>
#include <map>
#include <memory>
#include <stdexcept>


#define LOWER_CHARS "abcdefghijklmnopqrstuvwxyz"
#define UPPER_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SYMBOL_CHARS "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define DIGIT_CHARS "0123456789"


using namespace std;


map<standard_dict_id, shared_ptr<const dictionary> > standard_dictionary::dicts;


void standard_dictionary::init() {
    if(!dicts.empty()) {
        return;
    }

    create_dict(LOWER, LOWER_CHARS);
    create_dict(UPPER, UPPER_CHARS);
    create_dict(SYMBOL, SYMBOL_CHARS);
    create_dict(DIGIT, DIGIT_CHARS);
    create_dict(ALL, LOWER_CHARS UPPER_CHARS SYMBOL_CHARS DIGIT_CHARS);
}


shared_ptr<const dictionary> standard_dictionary::get(standard_dict_id id) {
    auto it = dicts.find(id);

    if(it == dicts.end()) {
        throw invalid_argument(boost::str(boost::format("standard dictionary %1% does not exist.") % id));
    }

    return it->second;
}


void standard_dictionary::create_dict(standard_dict_id id, const char *chars) {
    dicts[id] = make_shared<const char_std_dictionary>(chars);
}


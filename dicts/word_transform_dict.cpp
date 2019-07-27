#include "word_transform_dict.hpp"
#include "word_dictionary.hpp"
#include "../transform_type.hpp"
#include "../selector.hpp"
#include <boost/format.hpp>
#include <cstdint>
#include <string>
#include <stdexcept>


using namespace std;


word_transform_dict::word_transform_dict() : word_dict(), transform_types(NONE), combos(0) {}


word_transform_dict::word_transform_dict(const word_dictionary *word_dictionary, int transforms) 
        : word_dict(word_dictionary), transform_types(transforms) {
    this->compute_combinations();
}


void word_transform_dict::set_word_dict(const word_dictionary *word_dictionary) { 
    this->word_dict = word_dictionary; 
    this->compute_combinations();
}


void word_transform_dict::set_transform_types(int transforms) { 
    this->transform_types = transforms;
    this->compute_combinations();
}


void word_transform_dict::sel_append(string &pattern, selector &s) const {
}


void word_transform_dict::val_append(string &pattern, uint32_t index) const {
/*
    if(transform_types == NONE) {
        return value;
    }
    
    transform_type selected_transform = select_transform(s);
    
    return transform(*value, selected_transform);
    */
}


transform_type word_transform_dict::select_transform(selector &s) const {
    switch(this->transform_types) {
        case NONE:
        case ALL_LOWER:
        case ALL_UPPER:
        case CAPITALIZE:
            return static_cast<transform_type>(this->transform_types);
        case ALL_LOWER | ALL_UPPER:
            return s.get(2) ? ALL_UPPER : ALL_LOWER;
        case ALL_LOWER | CAPITALIZE:
            return s.get(2) ? CAPITALIZE : ALL_LOWER;
        case ALL_UPPER | CAPITALIZE:
            return s.get(2) ? CAPITALIZE : ALL_UPPER;
        case ALL_LOWER | ALL_UPPER | CAPITALIZE: {
            uint32_t rand_value = s.get(3);
            if(rand_value == 0)
                return ALL_LOWER;
            else if(rand_value == 1)
                return ALL_UPPER;
            else
                return CAPITALIZE;
        }
        default:
            throw invalid_argument(boost::str(boost::format("transform_type %1% is currently not supposed.") % this->transform_types));
    }
}


void word_transform_dict::compute_combinations() {
    int transform_count = ((this->transform_types & ALL_LOWER) > 0)
        + ((this->transform_types & ALL_UPPER) > 0)
        + ((this->transform_types & CAPITALIZE) > 0);

    if(transform_count == 0) {
        transform_count = 1;
    }

    this->combos = static_cast<uint32_t>(transform_count) * this->word_dict->combinations();
}


string word_transform_dict::transform(const string &value, transform_type selected_transform) const {
    string current_value = value;

    switch(selected_transform) {
        case NONE:
        case ALL_LOWER:    // assume NONE == ALL_LOWER for now
            break;
        case ALL_UPPER:
            std::transform(current_value.begin(), current_value.end(), current_value.begin(), ::toupper);
            break;
        case CAPITALIZE:
#ifdef _DEBUG
            current_value.at(0) = toupper(current_value.at(0));
#else
            current_value[0] = toupper(current_value[0]);
#endif
            break;
        default:
            throw invalid_argument(boost::str(boost::format("transform_type %1% is currently not supposed.") %
                 selected_transform));
    }

    return current_value;
}



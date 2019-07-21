#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "transform_type.hpp"
#include <string>
#include <vector>


using namespace std;

class standard_dictionary;
class selector;


class dictionary {
public:
    dictionary(const vector<string> *values);
    dictionary(const standard_dictionary &std_dict, int transform_types, int max_transform_count);

    const string *get(selector &s) const;
    double get_combinations() const;

private:
    transform_type select_transform(selector &s) const;
    const string *transform(const string &value, transform_type selected_transform) const;

    const vector<string> *values;
    int transform_types;
    int max_transform_count;

    mutable string current_value;
    mutable double combinations;
};


#endif

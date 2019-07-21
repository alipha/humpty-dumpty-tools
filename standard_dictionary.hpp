#ifndef STANDARD_DICTIONARY_HPP
#define STANDARD_DICTIONARY_HPP

#include <boost/utility.hpp>
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace boost;


enum standard_dict_id {
    LOWER = 'l',
    UPPER = 'u',
    SYMBOL = 's',
    DIGIT = 'd',
    ALL = 'a'
};


class standard_dictionary : noncopyable {
public:
    static void init();
    static const standard_dictionary &get(standard_dict_id id);

    bool is_transformable() const { return transformable; }
    const vector<string> *get_values() const { return &values; }
    double get_combinations(int transform_types) const;

private:
    static void create_dict(standard_dict_id id, const char *chars);

    bool transformable;
    vector<string> values;
    mutable map<int, double> combinations;

    static map<standard_dict_id, standard_dictionary> standard_dicts;
};

#endif

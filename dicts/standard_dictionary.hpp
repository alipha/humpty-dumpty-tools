#ifndef DICTS_STANDARD_DICTIONARY_HPP
#define DICTS_STANDARD_DICTIONARY_HPP

#include "dictionary.hpp"
#include <boost/utility.hpp>
#include <map>
#include <memory>

using namespace std;


enum standard_dict_id {
    LOWER = 'l',
    UPPER = 'u',
    SYMBOL = 's',
    DIGIT = 'd',
    ALL = 'a'
};


class standard_dictionary : boost::noncopyable {
public:
    standard_dictionary() = delete;

    static void init();
    static shared_ptr<const dictionary> get(standard_dict_id id);

private:
    static void create_dict(standard_dict_id id, const char *chars);

    static map<standard_dict_id, shared_ptr<const dictionary> > dicts;
};

#endif

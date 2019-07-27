#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "dicts/dictionary.hpp"
#include <vector>
#include <string>

using namespace std;

class selector;


class pattern {
public:
    pattern() : parts(), combos(0.0) {}
    
    string get(selector &s) const;
    double combinations() const;
    
private:
    vector<dictionary> parts;
    mutable double combos;
};


#endif

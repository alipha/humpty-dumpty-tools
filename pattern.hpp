#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "dictionary.hpp"
#include <vector>
#include <string>

using namespace std;

class selector;


class pattern {
public:
	pattern() : parts(),  combinations(0.0) {}
	
	string get(selector &s) const;
	double get_combinations() const;
	
private:
    vector<dictionary> parts;
	mutable double combinations;
};


#endif

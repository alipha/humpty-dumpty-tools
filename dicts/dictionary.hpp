#ifndef DICTS_DICTIONARY_HPP
#define DICTS_DICTIONARY_HPP

#include "../selector.hpp"
#include <cstdint>
#include <string>

using namespace std;


class dictionary {
public:
	virtual void sel_append(string &pattern, selector &s) const {
        this->val_append(pattern, s.get(this->combinations()));
    }

	virtual void val_append(string &pattern, uint32_t index) const = 0;
	virtual uint32_t combinations() const = 0;
};

#endif

#ifndef DICTS_RANGE_DICTIONARY_HPP
#define DICTS_RANGE_DICTIONARY_HPP

#include "dictionary.hpp"
#include <cstdint>
#include <string>

using namespace std;


class range_dictionary : public dictionary {
public:
	range_dictionary(char first_ch, char last_ch) : first(first_ch), last(last_ch) {}

	void set_range(char first_ch, char last_ch);

	void val_append(string &pattern, uint32_t index) const override;
	uint32_t combinations() const override;
	
private:
	char first;
	char last;
};

#endif

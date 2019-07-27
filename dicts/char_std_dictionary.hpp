#ifndef DICTS_CHAR_STD_DICTIONARY_HPP
#define DICTS_CHAR_STD_DICTIONARY_HPP

#include "dictionary.hpp"
#include <cstdint>
#include <string>

using namespace std;


class char_std_dictionary : public dictionary {
public:
	char_std_dictionary(const char *char_list);

	void set_chars(const char *char_list);	
	void val_append(string &pattern, uint32_t index) const override;

	uint32_t combinations() const override { return this->len; }
	
private:
	const char *chars;
	uint32_t len;
};

#endif

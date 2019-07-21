#include "standard_dictionary.hpp"
#include "transform_type.hpp"

#include <boost/format.hpp>
#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>


#define LOWER_CHARS "abcdefghijklmnopqrstuvwxyz"
#define UPPER_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SYMBOL_CHARS "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define DIGIT_CHARS "0123456789"


using namespace std;
using namespace boost;


map<standard_dict_id, standard_dictionary> standard_dictionary::standard_dicts;


void standard_dictionary::init() {
	if(!standard_dicts.empty()) {
		return;
	}

	create_dict(LOWER, LOWER_CHARS);
	create_dict(UPPER, UPPER_CHARS);
	create_dict(SYMBOL, SYMBOL_CHARS);
	create_dict(DIGIT, DIGIT_CHARS);
	create_dict(ALL, LOWER_CHARS UPPER_CHARS SYMBOL_CHARS DIGIT_CHARS);
}


const standard_dictionary &standard_dictionary::get(standard_dict_id id) {
	auto it = standard_dicts.find(id);

	if(it == standard_dicts.end()) {
		throw invalid_argument(str(format("stanard dictionary %1% does not exist.") % id));
	}

	return it->second;
}


double standard_dictionary::get_combinations(int transform_types) const {
	if(transform_types != NONE && !transformable) {
		throw invalid_argument(str(format("dictionary is not transformable and transform_type %1% was passed") 
			% transform_types));
	}

	double combos = combinations[transform_types];

	if(combos == 0.0) {
		// TODO: calculate combinations lazily for english dictionaries, etc
	}

	return combos;
}
	
	
void standard_dictionary::create_dict(standard_dict_id id, const char *chars) {
	size_t count;
	standard_dictionary &dict = standard_dicts[id];	// create dict

	for(count = 0; chars[count]; count++) {
		dict.values.push_back(string(1, chars[count]));
	}
	
	dict.transformable = false;
	dict.combinations[NONE] = count;
}


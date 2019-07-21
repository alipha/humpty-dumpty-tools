#include "dictionary.hpp"
#include "standard_dictionary.hpp"
#include "selector.hpp"
#include "transform_type.hpp"

#include <boost/format.hpp>
#include <boost/implicit_cast.hpp>
#include <cctype>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;
using namespace boost;


dictionary::dictionary(const vector<string> *v) : 
	values(v), 
	transform_types(NONE), 
	max_transform_count(0),
	current_value(),
	combinations(v->size()) {}


dictionary::dictionary(const standard_dictionary &std_dict, int transforms, int max_transforms) :
	values(std_dict.get_values()),
	transform_types(transforms),
	max_transform_count(max_transforms),
	current_value(),
	combinations(std_dict.get_combinations(transforms)) {}


const string *dictionary::get(selector &s) const {
	/* TODO: we really should have dictionary contain a:
		 map<int, map<int, std::string*>> running_combo_count;
		 where we do: running_combo_count[transform_types].lower_bound(s.get(combinations))
		 so that each possible word transformation is equally selected.
		 For MIXED, LEET_NUMBERS, and LEET_SYMBOLS, the number of possible transformations
		 changes per word, so first selecting a word and then selecting the transformations
		 doesn't produce a uniform distribution.
	*/
	uint32_t index = s.get(values->size());

#ifdef _DEBUG
	const string *value = &values->at(index);
#else	
	const string *value = &(*values)[index];
#endif

	if(transform_types == NONE) {
		return value;
	}
	
	transform_type selected_transform = select_transform(s);
	
	return transform(*value, selected_transform);
}


transform_type dictionary::select_transform(selector &s) const {
	switch(transform_types) {
		case NONE:
		case ALL_LOWER:
		case ALL_UPPER:
		case CAPITALIZE:
			return static_cast<transform_type>(transform_types);
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
			throw invalid_argument(str(format("transform_type %1% is currently not supposed.") % transform_types));
	}
}


double dictionary::get_combinations() const {
	if(combinations != 0.0) {
		return combinations;
	}

	int transform_count = ((transform_types & ALL_LOWER) > 0)
		+ ((transform_types & ALL_UPPER) > 0)
		+ ((transform_types & CAPITALIZE) > 0);

	if(transform_count == 0) {
		transform_count = 1;
	}

	return static_cast<size_t>(transform_count) * values->size();
}


const string *dictionary::transform(const string &value, transform_type selected_transform) const {
	current_value = value;

	switch(selected_transform) {
		case NONE:
		case ALL_LOWER:	// assume NONE == ALL_LOWER for now
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
			throw invalid_argument(str(format("transform_type %1% is currently not supposed.") %
				 selected_transform));
	}

	return &current_value;
}


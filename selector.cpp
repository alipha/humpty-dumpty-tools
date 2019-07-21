#include "selector.hpp"

#include <boost/format.hpp>
#include <stdexcept>

using namespace std;
using namespace boost;


selector::selector() : available_range(1), value(0), input(), bytes_used(0) {}


void selector::set_input(const uint8_t *src, size_t len) {
	if(len & 1) {
		throw invalid_argument(str(format("src len must be an even number. provided: %1%.") % len));
	}

	input.assign(src, src + len);
	available_range = 1;
	value = 0;
	bytes_used = 0;
}


/* algorithm credited to int-e from ##crypto on freenode */
uint32_t selector::get(uint32_t range) {
    // The key invariant is: value is uniformly random in [0, available_range)
    // and independent of all previous results of get().
	while(true) {
		while(available_range < (UINT64_C(1) << 47)) {
			available_range <<= 16;
			value = (value << 16) + consume_word();
		}

		if(value < available_range - available_range % range) {
			uint32_t result = value % range;
			// restore invariant: value is uniformly random in [0, available_range)
            // in addition we know that available_range is a multiple of range now.
			// this division is uniform because of the above if condition.
			available_range /= range;
			value /= range;
			return result;
		}

		// value is uniformly random in [available_range - available_range % range, available_range)
        // restore invariant...
		available_range %= range;
		value %= range;
	}
}


uint16_t selector::consume_word() {
	bytes_used += 2;
	if(bytes_used > input.size()) {
		throw runtime_error(str(format("input source of %1% bytes depleted.") % input.size()));
	}

#if _DEBUG
	return (input.at(bytes_used - 1) << 8) | input.at(bytes_used - 2);
#else
	return (input[bytes_used - 1] << 8) | input[bytes_used - 2];
#endif
}


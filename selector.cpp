#include "selector.hpp"

#include <boost/format.hpp>
#include <stdexcept>

using namespace std;


selector::selector() : available_range(1), value(0), input(), bytes_used(0) {}


void selector::set_input(const uint8_t *src, size_t len) {
    if(len & 1) {
        throw invalid_argument(boost::str(boost::format("src len must be an even number. provided: %1%.") % len));
    }

    this->input.assign(src, src + len);
    this->available_range = 1;
    this->value = 0;
    this->bytes_used = 0;
}


/* algorithm credited to int-e from ##crypto on freenode */
uint32_t selector::get(uint32_t range) {
    // The key invariant is: value is uniformly random in [0, available_range)
    // and independent of all previous results of get().
    while(true) {
        while(this->available_range < (UINT64_C(1) << 47)) {
            this->available_range <<= 16;
            this->value = (this->value << 16) + this->consume_word();
        }

        if(this->value < this->available_range - this->available_range % range) {
            uint32_t result = this->value % range;
            // restore invariant: value is uniformly random in [0, available_range)
            // in addition we know that available_range is a multiple of range now.
            // this division is uniform because of the above if condition.
            this->available_range /= range;
            this->value /= range;
            return result;
        }

        // value is uniformly random in [available_range - available_range % range, available_range)
        // restore invariant...
        this->available_range %= range;
        this->value %= range;
    }
}


uint16_t selector::consume_word() {
    this->bytes_used += 2;
    if(this->bytes_used > this->input.size()) {
        throw runtime_error(boost::str(boost::format("input source of %1% bytes depleted.") % this->input.size()));
    }

#if _DEBUG
    return (this->input.at(this->bytes_used - 1) << 8) | this->input.at(this->bytes_used - 2);
#else
    return (this->input[this->bytes_used - 1] << 8) | this->input[this->bytes_used - 2];
#endif
}


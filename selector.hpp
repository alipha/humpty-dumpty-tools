#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <boost/utility.hpp>
#include <cstdint>
#include <cstddef>
#include <vector>


using namespace std;
using namespace boost;


class selector : noncopyable {
public:
    selector();
    void set_input(const uint8_t *src, size_t len);

    uint32_t get(uint32_t range);

private:
    uint16_t consume_word();
    
    uint64_t available_range;
    uint64_t value;
    vector<uint8_t> input;
    size_t bytes_used;
};


#endif

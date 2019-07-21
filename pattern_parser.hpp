#include "pattern.hpp"
#include <boost/utility.hpp>
#include <string>


using namespace std;
using namespace boost;


class pattern_parser : noncopyable {
public:
    pattern_parser();

    pattern parse(const string &input) const;

private:
};


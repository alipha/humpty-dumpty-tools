#include "pattern.hpp"
#include <boost/utility.hpp>
#include <string>


using namespace std;


class pattern_parser : boost::noncopyable {
public:
    pattern_parser();

    pattern parse(const string &input) const;

private:
};


#include <enum.h>
#include <iostream>
#include <type_traits>

#define VX3 DEF_ENUM_SEQUENCE(v1, v2, v3)

DEF_ENUM_IN_NS_S(t1, VX3)
DEF_N4428_S(t1, VX3)

namespace n {
DEF_ENUM_IN_NS_S(t1, VX3)
}
DEF_N4428_SCOPED_S(t1, n, VX3)

class c {
    public:
    DEF_ENUM_IN_CLASS_S(t1, VX3)
};
DEF_N4428_SCOPED_S(t1, c, VX3)

template <class EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
std::ostream& operator<<(std::ostream& os, EnumT const& t)
{
    return os << static_cast<int>(t);
}

int main()
{
    for (auto const& v : std::enum_traits<t1>::values())
        std::cout << enum_to_str(v) << ": " << v << "\n";

    for (auto const& v : t1_values)
        std::cout << enum_to_str(v) << ": " << v << "\n";

    for (auto const& v : n::t1_values)
        std::cout << enum_to_str(v) << ": " << v << "\n"; // koenig lookup of n::enum_to_str

    for (auto const& k : std::enum_traits<n::t1>::names())
        std::cout << k << ": " << n::str_to_t1(k) << "\n";

    for (auto const& k : std::enum_traits<n::t1>::names())
        std::cout << k << ": " << std::enum_traits<n::t1>::from_string(k) << "\n";
    std::flush(std::cout);
}

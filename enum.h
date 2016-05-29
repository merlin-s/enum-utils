#ifndef ENUM_UTILS_H_INCLUDED
#define ENUM_UTILS_H_INCLUDED
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/reverse.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#include <array>
#include <cstring>

#ifndef EUs_N4428_NS
#define EUs_N4428_NS std
#endif
namespace EUs_N4428_NS {
template <class Enum> struct enum_traits {
    struct enumerators {
        // static constexpr size_t const size;
        // template <size_t I> struct get {
        //    static constexpr char const* const identifier;
        //    static constexpr Enum const value;
        // };
    };
    // constexpr static std::array<Enum, size> const& values();
    // constexpr static std::array<const char*, size> const& names();
};
}
#define EUs_str_type const char*
#define EUs_str_cmp 0 == std::strcmp
#define EUs_scoped_elem(r, data, elem) data::elem
#define EUs_scoped_elem_c(r, data, elem) data::elem,
#define EUs_string_elem(r, data, elem) BOOST_PP_STRINGIZE(elem)
#define EUs_string_elem_c(r, data, elem) BOOST_PP_STRINGIZE(elem),
#define EUs_traits_enumerator_get(r, data, elem)                                                                       \
    template <> struct enum_traits<data>::enumerators::get<BOOST_PP_SUB(r, 2)> {                                       \
        static constexpr char const* const identifier = BOOST_PP_STRINGIZE(elem);                                      \
        static constexpr const data value = data::elem;                                                                \
    };

#define EUs_back(seq) BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(seq))

#define EUs_foreach_lastspecial(seq, data, macro, macro_last)                                                          \
    BOOST_PP_SEQ_FOR_EACH(macro, data, BOOST_PP_SEQ_POP_BACK(seq))                                                     \
    macro_last(0, data, EUs_back(seq))

#define EUs_enum_s_internal(name, seq, count, static)                                                                  \
    enum class name { BOOST_PP_SEQ_ENUM(seq) };                                                                        \
    constexpr static const std::array<name, count> name##_values                                                       \
        = { { EUs_foreach_lastspecial(seq, name, EUs_scoped_elem_c, EUs_scoped_elem) } };                              \
    constexpr static std::array<EUs_str_type const, count> name##_names                                                \
        = { { EUs_foreach_lastspecial(seq, name, EUs_string_elem_c, EUs_string_elem) } };                              \
    constexpr static EUs_str_type enum_to_str(name n) { return name##_names[static_cast<std::size_t>(n)]; }            \
    name str_to_##name(EUs_str_type const& str)                                                                        \
    {                                                                                                                  \
        for (std::size_t i = 0; i < static_cast<std::size_t>(count); ++i) {                                            \
            if (EUs_str_cmp(str, name##_names[i]))                                                                     \
                return static_cast<name>(i);                                                                           \
        }                                                                                                              \
        throw std::runtime_error("invalid enum name");                                                                 \
    }

#define EUs_enum_n4428_s_internal(name, count, scope, seq)                                                             \
    namespace EUs_N4428_NS {                                                                                           \
        template <> struct enum_traits<scope::name> {                                                                  \
            struct enumerators {                                                                                       \
                static const constexpr size_t size = BOOST_PP_SEQ_SIZE(seq);                                           \
                template <size_t I> struct get {                                                                       \
                };                                                                                                     \
            };                                                                                                         \
            constexpr static decltype(scope::name##_values) const& values() { return scope::name##_values; }           \
            constexpr static decltype(scope::name##_names) const& names() { return scope::name##_names; }              \
            static scope::name from_string(EUs_str_type const& str) { return scope::str_to_##name(str); }              \
            constexpr static EUs_str_type to_string(scope::name n) { return scope::enum_to_str(n); }                   \
        };                                                                                                             \
        BOOST_PP_SEQ_FOR_EACH(EUs_traits_enumerator_get, scope::name, seq)                                             \
    }

#define DEF_N4428_SCOPED_S(name, scope, seq) EUs_enum_n4428_s_internal(name, BOOST_PP_SEQ_SIZE(seq), scope, seq)
#define DEF_N4428_S(name, seq) EUs_enum_n4428_s_internal(name, BOOST_PP_SEQ_SIZE(seq), BOOST_PP_EMPTY(), seq)

#define DEF_ENUM_SEQUENCE BOOST_PP_VARIADIC_TO_SEQ
#define DEF_ENUM_IN_NS_S(name, seq) EUs_enum_s_internal(name, seq, BOOST_PP_SEQ_SIZE(seq), BOOST_PP_EMPTY())
#define DEF_ENUM_IN_CLASS_S(name, seq) EUs_enum_s_internal(name, seq, BOOST_PP_SEQ_SIZE(seq), static)

#define DEF_ENUM_IN_NS(name, ...) DEF_ENUM_IN_NS_S(name, DEF_ENUM_SEQUENCE(__VA_ARGS__))
#define DEF_ENUM_IN_CLASS(name, ...) DEF_ENUM_IN_CLASS_S(name, DEF_ENUM_SEQUENCE(__VA_ARGS__))

#endif /* end of include guard: ENUM_UTILS_H_INCLUDED */

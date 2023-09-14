#ifndef INCLUDE_PKG_TEST_HPP
#define INCLUDE_PKG_TEST_HPP

#include <cctype>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Custom exception class for test failures
 */
namespace test {

struct check_error : public std::exception {
private:
    const std::string what_arg;

public:
    /**
     * @brief Constructor for check_error object
     * 
     * @param msg The error message
     */
    check_error(std::string msg);

    /**
     * @brief Constructor for check_error object
     * 
     * @param msg The error message as a C-string
     */
    check_error(const char* msg);

    /**
     * @brief Get the error message
     * 
     * @return const char* The error message
     */
    const char* what() const noexcept override;
};

/**
 * @brief Call a list of test functions and send results.
 * 
 * @param funcs A vector of test functions
 * @param func_names A vector of test function names
 */
void call_tests(std::vector<std::function<void()>>&& funcs,
    std::vector<std::string>&& func_names = {});

// ("this is a test", ' ') -> {"this", "is", "a", "test"}
/**
 * @brief Split a string into a vector of substrings based on a delimiter.
 * 
 * 
 * @return A vector of substrings.
 */
std::vector<std::string> split(const std::string& str, char delim);

/**
 * @brief Remove leading and trailing whitespaces from a string.
 * 
 * @return The resulting string.
 */
std::string trim(const std::string& str);

// terminal echo modifiers
struct Color {
private:
    const std::string arg;
    Color(const char* arg);
    operator std::string() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    static Color Default();
    static Color Red();
    static Color Blue();
    static Color Green();
    static Color Orange();
};

std::ostream& operator<<(std::ostream& os, const Color& color);

} // namespace test

////////////
// MACROS //
////////////

/*
Do NOT use this macro with raw enclosed curly brackets
// DEBUG({ 1 }); // unresolvable error
see the error message of the following line:
// std::cout << { 1 } << std::endl; // ERROR
explicit initialization of an initializer list is OK
// std::cout << std::initializer_list<int>({ 1 }) << std::endl; // OK
*/
#define DEBUG(cc)                                                             \
    do {                                                                      \
        std::cout << ::test::Color::Blue() << #cc << ::test::Color::Default() \
                  << " = " << cc << std::endl;                                \
    } while (false)

// see note in DEBUG
#define DEBUG_MULTILINE(cc)                                                   \
    do {                                                                      \
        std::cout << ::test::Color::Blue() << #cc << ::test::Color::Default() \
                  << " =" << std::endl;                                       \
        std::cout << cc << std::endl;                                         \
    } while (false)

// throw check_error if condition is not met
#define CHECK(cond)                                                               \
    do {                                                                          \
        if (!(cond)) {                                                            \
            std::ostringstream __os;                                              \
            __os << ::test::Color::Red() << "Error: " << ::test::Color::Default() \
                 << #cond << "\n";                                                \
            __os << ::test::Color::Red() << "File: " << ::test::Color::Default()  \
                 << __FILE__ << "\n";                                             \
            __os << ::test::Color::Red() << "Line: " << ::test::Color::Default()  \
                 << __LINE__ << "\n";                                             \
            throw ::test::check_error(__os.str());                                \
        }                                                                         \
    } while (false)

// helper macro
#define __CHECK_COND(cond, a, b)                                                     \
    do {                                                                             \
        if (!(cond)) {                                                               \
            std::ostringstream __os;                                                 \
            __os << ::test::Color::Red() << "Error: " << ::test::Color::Default()    \
                 << #cond << "\n";                                                   \
            __os << ::test::Color::Red() << "File: " << ::test::Color::Default()     \
                 << __FILE__ << "\n";                                                \
            __os << ::test::Color::Red() << "Line: " << ::test::Color::Default()     \
                 << __LINE__ << "\n";                                                \
            __os << ::test::Color::Blue() << #a << ::test::Color::Default() << " = " \
                 << (a) << "\n";                                                     \
            __os << ::test::Color::Blue() << #b << ::test::Color::Default() << " = " \
                 << (b) << "\n";                                                     \
            throw ::test::check_error(__os.str());                                   \
        }                                                                            \
    } while (false)

#define CHECK_EQ(a, b) __CHECK_COND(std::equal_to<>()(a, b), a, b)
#define CHECK_NE(a, b) __CHECK_COND(std::not_equal_to<>()(a, b), a, b)
#define CHECK_GT(a, b) __CHECK_COND(std::greater<>()(a, b), a, b)
#define CHECK_GE(a, b) __CHECK_COND(std::greater_equal<>()(a, b), a, b)
#define CHECK_LT(a, b) __CHECK_COND(std::less<>()(a, b), a, b)
#define CHECK_LE(a, b) __CHECK_COND(std::less_equal<>()(a, b), a, b)

// helper macro
#define __CHECK_COND_DEBUG(cond, a, b)                                          \
    do {                                                                        \
        if (cond) {                                                             \
            std::cout << ::test::Color::Blue()                                  \
                      << "Condition met: " << ::test::Color::Default() << #cond \
                      << std::endl;                                             \
        } else {                                                                \
            __CHECK_COND(cond, a, b);                                           \
        }                                                                       \
    } while (false)

#define CHECK_EQ_DEBUG(a, b) __CHECK_COND_DEBUG(std::equal_to<>()(a, b), a, b)
#define CHECK_NE_DEBUG(a, b) \
    __CHECK_COND_DEBUG(std::not_equal_to<>()(a, b), a, b)
#define CHECK_GT_DEBUG(a, b) __CHECK_COND_DEBUG(std::greater<>()(a, b), a, b)
#define CHECK_GE_DEBUG(a, b) \
    __CHECK_COND_DEBUG(std::greater_equal<>()(a, b), a, b)
#define CHECK_LT_DEBUG(a, b) __CHECK_COND_DEBUG(std::less<>()(a, b), a, b)
#define CHECK_LE_DEBUG(a, b) __CHECK_COND_DEBUG(std::less_equal<>()(a, b), a, b)

// usage: RUN_TESTS(func1, func2, func3)
// functions must be void(*)(void)
#define RUN_TESTS(...)                                                         \
    do {                                                                       \
        ::test::call_tests({ __VA_ARGS__ }, ::test::split(#__VA_ARGS__, ',')); \
    } while (false)

////////////////////////
// INLINE DEFINITIONS //
////////////////////////

namespace test {

inline check_error::check_error(std::string msg)
    : what_arg(msg)
{
}
inline check_error::check_error(const char* msg)
    : what_arg(msg)
{
}
inline const char* check_error::what() const noexcept
{
    return what_arg.c_str();
}

inline void call_tests(std::vector<std::function<void()>>&& funcs,
    std::vector<std::string>&& func_names)
{
    if (func_names.empty()) {
        func_names.resize(funcs.size());
    }
    CHECK_EQ(funcs.size(), func_names.size());
    int num_tests = 0;
    int success = 0;
    for (size_t i = 0; i < funcs.size(); i++) {
        try {
            std::cout << ::test::Color::Orange() << "\nTest #" << ++num_tests;
            func_names[i] = trim(func_names[i]);
            if (!func_names[i].empty()) {
                std::cout << " : " << func_names[i];
            }
            std::cout << ::test::Color::Default() << std::endl;
            funcs[i]();
            ++success;
            std::cout << ::test::Color::Green() << "Test #" << num_tests
                      << " succeeded!\n";
        } catch (const check_error& e) {
            std::cerr << "\n\n"
                      << e.what() << std::endl;
        }
        std::cout << "\n\n"
                  << std::flush;
    }
    std::cout << ::test::Color::Green() << "\n"
              << success << "/" << num_tests << " tests passed"
              << ::test::Color::Default() << std::endl;
}

inline std::vector<std::string> split(const std::string& str, char delim)
{
    std::vector<std::string> res;
    std::istringstream os(str);
    std::string temp;
    while (std::getline(os, temp, delim)) {
        res.push_back(temp);
    }
    return res;
}

inline std::string trim(const std::string& str)
{
    auto it = str.cbegin();
    while (it != str.cend() && std::isspace(*it)) {
        ++it;
    }
    auto rit = str.crbegin();
    while (rit.base() != it && std::isspace(*rit)) {
        ++rit;
    }
    return std::string(it, rit.base());
}

inline Color::Color(const char* arg)
    : arg(arg)
{
}
inline Color::operator std::string() const { return arg; }

#ifdef __linux__
inline Color Color::Default()
{
    return "\033[0m";
}
inline Color Color::Red() { return "\033[0;31m"; }
inline Color Color::Blue() { return "\033[0;34m"; }
inline Color Color::Green() { return "\033[0;32m"; }
inline Color Color::Orange() { return "\033[0;33m"; }
#endif // __linux__

inline std::ostream& operator<<(std::ostream& os, const Color& color)
{
    return os << static_cast<std::string>(color);
}

} // namespace test

#endif // INCLUDE_PKG_TEST_HPP

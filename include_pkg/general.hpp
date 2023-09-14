#ifndef INCLUDE_PKG_GENERAL_HPP
#define INCLUDE_PKG_GENERAL_HPP

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace general {

// format like printf
// also see std::format (C++20)
template <typename... Args>
std::string format(const std::string& format, Args... args);

std::string tolower(std::string s);

std::string toupper(std::string s);

/*
algorithm to print a range
Example usage:
  std::vector<int> vec{1, 2, 3};
  print_range(std::cout, vec.begin(), vec.end());
Output:
  {1, 2, 3}
*/
template <typename BidIt>
std::ostream& print(std::ostream& os, BidIt beg, BidIt end,
    const char encloser[2] = "{}",
    const char* separator = ", ");

} // namespace general

////////////////////////
// INLINE DEFINITIONS //
////////////////////////

namespace general {

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf/26221725#26221725
template <typename... Args>
inline std::string format(const std::string& format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(),
        buf.get() + size - 1); // We don't want the '\0' inside
}

// https://en.cppreference.com/w/cpp/string/byte/tolower
inline std::string tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}

// https://en.cppreference.com/w/cpp/string/byte/toupper
inline std::string toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return s;
}

template <typename BidIt>
std::ostream& print(std::ostream& os, BidIt beg, BidIt end,
    const char encloser[2], const char* separator)
{
    os << encloser[0];
    if (std::distance(beg, end) > 0) {
        BidIt last = std::prev(end);
        while (beg != last) {
            os << *beg++ << separator;
        }
        os << *last;
    }
    return os << encloser[1];
}

} // namespace general

#endif // INCLUDE_PKG_GENERAL_HPP

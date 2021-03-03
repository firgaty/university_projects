#ifndef INCLUDE_UTIL_CONVERT_HPP_
#define INCLUDE_UTIL_CONVERT_HPP_

#include <codecvt>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

class Convert
{

public:

    static std::string to_utf8(const std::u16string &s)
    {
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
        return conv.to_bytes(s);
    }

    static std::string to_utf8(const std::u32string &s)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
        return conv.to_bytes(s);
    }

    static std::u16string to_utf16(const std::string &s)
    {
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
        return convert.from_bytes(s);
    }

    static std::u32string to_utf32(const std::string &s)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
        return conv.from_bytes(s);
    }

    static std::u16string to_utf16(const std::u32string &s)
    {
        return to_utf16(to_utf8(s));
    }

    static std::u32string to_utf32(const std::u16string &s)
    {
        return to_utf32(to_utf8(s));
    }
};

#endif // !INCLUDE_UTIL_CONVERT_HPP_
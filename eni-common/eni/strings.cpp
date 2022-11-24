//
// Created by void on 14/07/2021.
//

#include "strings.h"

namespace eni::strings {

std::wstring toWide(const std::string &str) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string fromWide(const std::wstring &wideStr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wideStr);
}

}// namespace eni::strings

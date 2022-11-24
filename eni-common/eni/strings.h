//
// Created by void on 14/07/2021.
//

#ifndef ENI_STRINGS_H
#define ENI_STRINGS_H

#include <codecvt>
#include <locale>
#include <string>

namespace eni::strings {

/**
 * Converts an ANSI string to UTF-8.
 * @param str The string to convert.
 * @return The converted wide string.
 */
[[nodiscard]] std::wstring toWide(const std::string &str);

/**
 * Converts a UTF-8 string to ANSI. Use carefully, this is not a lossless conversion and mostly used internally in situations where wide strings are not supported (yet).
 *
 * @param str The wide string to convert.
 * @return The converted string.
 */
[[nodiscard]] std::string fromWide(const std::wstring &wideStr);

}// namespace eni::strings

#endif//ENI_STRINGS_H

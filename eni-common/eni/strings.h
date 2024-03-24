//
// Created by void on 14/07/2021.
//

#ifndef ENI_STRINGS_H
#define ENI_STRINGS_H

#include <locale>
#include <sstream>
#include <string>
#include <vector>

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
[[nodiscard]] std::string fromWide(const std::wstring &str);

/**
 * Trims a string by removing characters from its left and right.
 * @param str The string to trim.
 * @param chars The characters to remove.
 */
extern void trim(std::string &str, const std::string &chars = " \t\n\r");

/**
 * Trims a string by removing characters from its left and right.
 * @param str The string to trim.
 * @param chars The characters to remove.
 */
extern void trim(std::wstring &str, const std::wstring &chars = L" \t\n\r");

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separators A list of separators.
 * @param trim Whether to trim the tokens.
 * @param skipEmpty Whether to skip empty tokens.
 * @param keepSeparators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
extern std::vector<std::string> tokenize(const std::string &str,
                                         const std::vector<std::string> &separators,
                                         bool trim = true, bool skipEmpty = true,
                                         bool keepSeparators = false);

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separators A list of separators.
 * @param trim Whether to trim the tokens.
 * @param skipEmpty Whether to skip empty tokens.
 * @param keepSeparators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
extern std::vector<std::wstring>
tokenize(const std::wstring &str, const std::vector<std::wstring> &separators,
         bool trim = true, bool skipEmpty = true,
         bool keepSeparators = false);

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separator The separator.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
inline std::vector<std::string> tokenize(const std::string &str, const std::string &separator,
                                         bool trim = true, bool skip_empty = true,
                                         bool keep_separators = false) {
    return tokenize(str, std::vector({separator}), trim, skip_empty,
                    keep_separators);
}

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separator The separator.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
inline std::vector<std::wstring>
tokenize(const std::wstring &str, const std::wstring &separator, bool trim = true,
         bool skip_empty = true, bool keep_separators = false) {
    return tokenize(str, std::vector<std::wstring>({separator}), trim, skip_empty,
                    keep_separators);
}

/**
 * Joins a list of strings into a new string.
 * @param separator The separator to put between the string components.
 * @param components The components list.
 * @return The joined string.
 */
extern std::string join(const std::string &separator,
                        const std::vector<std::string> &components);

/**
 * Joins a list of strings into a new string.
 * @param separator The separator to put between the string components.
 * @param components The components list.
 * @return The joined string.
 */
extern std::wstring join(const std::wstring &separator,
                         const std::vector<std::wstring> &components);

/**
 * Converts a string to snake_case.
 * @param str The string.
 * @return The converted string.
 */
extern std::string toSnakeCase(const std::string &str);

/**
 * Converts a string to kebab-case.
 * @param str The string.
 * @return The converted string.
 */
extern std::string toKebabCase(const std::string &str);

/**
 * Converts a string to camelCase.
 * @param str The string.
 * @param capitalizeFirstLetter Whether to begin the string with a capital
 * letter.
 * @return The converted string.
 */
extern std::string toCamelCase(const std::string &str,
                               bool capitalizeFirstLetter = false);

/**
 * Converts a string to upper case.
 * @param str The string.
 * @return The converted string.
 */
extern std::string toUppercase(const std::string &str);

/**
 * Converts a string to lower case.
 * @param str The string.
 * @return The converted string.
 */
extern std::string toLowercase(const std::string &str);

/**
 * Implodes a list of elements into a string.
 * @tparam T The type of the elements to implode, must be string-convertible.
 * @tparam ContainerT The container type, must support range-based-for loops.
 * @param separator The separator to put between the imploded elements.
 * @param container The container of elements.
 * @return The imploded string.
 */
template<typename T, typename ContainerT = std::vector<T>>
std::string implode(const std::string &separator, const ContainerT &container) {
    std::stringstream ss;
    bool first = true;
    for (auto &s : container) {
        if (!first) {
            ss << separator;
        } else {
            first = false;
        }
        ss << s;
    }
    return ss.str();
}

/**
 * Implodes a list of elements into a string.
 * @tparam T The type of the elements to implode, must be string-convertible.
 * @tparam ContainerT The container type, must support range-based-for loops.
 * @param separator The separator to put between the imploded elements.
 * @param container The container of elements.
 * @return The imploded string.
 */
template<typename T, typename ContainerT = std::vector<T>>
std::wstring implode(const std::wstring &separator, const ContainerT &container) {
    std::wstringstream ss;
    bool first = true;
    for (auto &s : container) {
        if (!first) {
            ss << separator;
        } else {
            first = false;
        }
        ss << s;
    }
    return ss.str();
}

}// namespace eni::strings

#endif//ENI_STRINGS_H

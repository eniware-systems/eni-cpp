//
// Created by void on 14/07/2021.
//

#include <algorithm>
#include <eni/strings.h>

#include <codecvt>

namespace eni::strings {

std::wstring toWide(const std::string &str) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX> converterX;

    return converterX.from_bytes(str);
}

std::string fromWide(const std::wstring &wideStr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX> converterX;

    return converterX.to_bytes(wideStr);
}

void trim(std::string &str, const std::string &chars) {
    auto from = str.find_first_not_of(chars);
    auto to = str.find_last_not_of(chars);
    if (to != std::string::npos) {
        str.erase(to + 1, str.length() - 1);
    }
    if (from != std::string::npos) {
        str.erase(0, from);
    }
}

void trim(std::wstring &str, const std::wstring &chars) {
    auto from = str.find_first_not_of(chars);
    auto to = str.find_last_not_of(chars);

    if (from == std::wstring::npos && to == std::wstring::npos) {
        str.clear();
    }

    if (to != std::wstring::npos && to < str.length() - 1) {
        str.erase(to + 1, str.length() - 1);
    }
    if (from != std::wstring::npos) {
        str.erase(0, from);
    }
}

std::vector<std::string> tokenize(const std::string &str,
                                  const std::vector<std::string> &separators, const bool trim,
                                  const bool skipEmpty, const bool keepSeparators) {
    std::vector<std::wstring> separatorsW;

    separatorsW.reserve(separators.size());
    for (const auto &separator : separators) {
        separatorsW.push_back(toWide(separator));
    }

    auto wr = tokenize(toWide(str), separatorsW, trim, skipEmpty,
                       keepSeparators);
    std::vector<std::string> r;
    r.reserve(wr.size());
    for (auto &wstr : wr) {
        r.push_back(fromWide(wstr));
    }
    return r;
}

std::vector<std::wstring> tokenize(const std::wstring &str,// NOLINT(*-function-cognitive-complexity)
                                   const std::vector<std::wstring> &separators,
                                   const bool trim,
                                   const bool skipEmpty, const bool keepSeparators) {
    // since find_first_of seeks for any char in the given string, we need to make
    // substring checks here
    std::wstring::size_type n = 0;
    std::wstring::size_type offset = 0;
    std::vector<std::wstring> r;

    while (n < str.length()) {
        bool found = false;
        for (const auto &separator : separators) {
            if (n + separator.length() >= str.length()) {
                continue;
            }
            std::wstring sub = str.substr(n, separator.length());
            if (sub == separator) {
                found = true;
                std::wstring token = str.substr(offset, n - offset);
                if (trim) {
                    strings::trim(token);
                }
                n += separator.length();
                offset = n;
                if (!skipEmpty || !token.empty()) {
                    if (!token.empty() ||
                        !r.empty()) {// Do not allow first token to be empty.
                        r.push_back(token);
                    }
                }

                if (keepSeparators) {
                    r.push_back(sub);
                }
                break;
            }
        }
        if (!found) {
            ++n;
        }
    }

    if (auto remaining = str.substr(offset); !remaining.empty()) {
        if (trim) {
            strings::trim(remaining);
        }

        r.push_back(remaining);
    }

    return r;
}

std::string toSnakeCase(const std::string &str) {
    const auto tokens = tokenize(str, std::vector<std::string>({" ", "\t", "-", "_"}), true,
                                 true, false);
    auto s = implode<std::string>("_", tokens);
    std::ranges::transform(s, s.begin(), ::tolower);
    return s;
}

std::string toKebabCase(const std::string &str) {
    const auto tokens = tokenize(str, std::vector<std::string>({" ", "\t", "-", "_"}), true,
                                 true, false);
    auto s = implode<std::string>("-", tokens);
    std::ranges::transform(s, s.begin(), ::tolower);
    return s;
}

std::string toCamelCase(const std::string &str, const bool capitalizeFirstLetter) {
    auto tokens = tokenize(str, std::vector<std::string>({" ", "\t", "-", "_"}), true,
                           true, false);
    std::stringstream ss;
    bool first = true;
    for (auto &t : tokens) {
        if (!first || capitalizeFirstLetter) {
            ss << std::toupper(t[0]);
            ss << t.substr(1);
        } else /*if (first)*/ {
            first = false;
            ss << t;
        }
    }
    return ss.str();
}

std::string toUppercase(const std::string &str) {
    auto result = str;
    std::ranges::transform(result, result.begin(), ::toupper);
    return result;
}

std::string toLowercase(const std::string &str) {
    auto result = str;
    std::ranges::transform(result, result.begin(), ::tolower);
    return result;
}

std::string join(const std::string &separator, const std::vector<std::string> &components) {
    std::string result;
    bool first = true;

    for (const std::string &c : components) {
        if (!first) {
            result += separator;
        } else {
            first = false;
        }

        result += c;
    }
    return result;
}

std::wstring join(const std::wstring &separator,
                  const std::vector<std::wstring> &components) {
    std::wstring result;
    bool first = true;

    for (const std::wstring &c : components) {
        if (!first) {
            result += separator;
        } else {
            first = false;
        }

        result += c;
    }
    return result;
}

}// namespace eni::strings

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <variant>
#include <string>
#include <string_view>
#include <charconv>
#include <regex>
#include <optional>
struct JsonObject {
    std::variant<std::monostate, bool, int, float, double, std::string, std::vector<JsonObject>, std::map<std::string, JsonObject>> inner;
};

template <class T>
std::optional<T> try_parse_num(std::string_view str)
{
    T value;
    auto res = std::from_chars(str.data(), str.data() + str.size(), value);
    if (res.ec == std::errc() && res.ptr == str.data() + str.size()) {
        return value;
    }
    return std::nullopt;
}

JsonObject parser(std::string_view json)
{
    if (json.empty()) {
        return JsonObject { std::nullptr_t {} };
    }

    if ('0' <= json[0] && json[0] <= '9' || json[0] == '-' || json[0] == '+') {
        std::regex mun_re { "[+-]?[0-9]+(\\.[0-9]*)?([eE][+-]?[0-9]+)?" };
        std::cmatch match;
        if (std::regex_search(json.data(), json.data() + json.size(), match, mun_re)) {
            std::string str = match.str();
            {
                auto num = try_parse_num<int>(str);
                if (num.has_value()) {
                    return JsonObject { num.value() };
                }
            }
            {
                auto num = try_parse_num<double>(str);
                if (num.has_value()) {
                    return JsonObject { num.value() };
                }
            }
        }
    }
    return JsonObject { std::nullptr_t {} };
}

int main()
{
    std::string s = "3.14";
    JsonObject j = parser(s);
    time_t t
        = clock();
    tm* lt = localtime(&t);
    std::cout << "当前时间：" << asctime(lt);
    return 0;
}
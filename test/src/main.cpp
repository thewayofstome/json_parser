#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <variant>
#include <string>
#include <string_view>
struct JsonObject {
    std::variant<std::monostate, bool, int, float, double, std::string, std::vector<JsonObject>, std::map<std::string, JsonObject>> inner;
};

JsonObject parser(std::string_view json)
{
    if (json.empty()) {
        return JsonObject { std::nullptr_t {} };
    }

    return JsonObject { std::nullptr_t {} };
}

int main()
{
    std::string 
    parser();
    time_t t
        = clock();
    tm* lt = localtime(&t);
    std::cout << "当前时间：" << asctime(lt);
    return 0;
}
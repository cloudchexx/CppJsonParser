#include "JSONValue.h"

// JSONValue 类的实现
// JSONValue构造函数
JSONValue::JSONValue(std::string& json)
: JsonString{std::move(json)} // 默认初始化为一个空的 JSON 对象字符串
{
    std::cout << "We create a JSONValue" << std::endl;
}

std::string_view JSONValue::get_JSONString() const {
    return JsonString; // 返回存储的 JSON 字符串
}

// JSON_Null 类的实现
// 构造函数 构造JSON_Null对象
JSON_Null::JSON_Null(std::string& json)
: JSONValue{std::move(json)} // 调用基类构造函数初始化 JSONValue 部分
{
    std::cout << "We create a JSON_Null" << std::endl;
}
// 获取 JSON 值的类型
JSONValue::JSONType JSON_Null::getType() const {
    return JSONType::JSON_Null; // 返回 JSON_Null 类型
}
std::unique_ptr<JSONValue> JSON_Null::asValue_of_JSON() const {
    return std::make_unique<JSON_Null>(*this); // 返回一个新的 JSON_Null 对象
}

// JSON_Boolean 类的实现
// 构造函数 构造JSON_Boolean对象
JSON_Boolean::JSON_Boolean(std::string& json , bool val)
: JSONValue(json)
, value{val} // 初始化布尔值
{
    std::cout << "We create a JSON_Boolean" << std::endl;
}
// 获取 JSON 值的类型
JSONValue::JSONType JSON_Boolean::getType() const {
    return JSONType::JSON_Boolean; // 返回 JSON_Boolean 类型
}
std::unique_ptr<JSONValue> JSON_Boolean::asValue_of_JSON() const {
    return std::make_unique<JSON_Boolean>(*this); // 返回一个新的 JSON_Boolean 对象
}

// 暂时没有写完
#include <iostream>
#include "Tokenizer.h"
#include "JSONValue.h"

// 这是一个递归函数会递归调用自己来一层一层解析JSON字符串，直到最小单元的JSON对象被创建
JSONValue& parseJSON(const std::string& jsonString) {
    // 这里应该实现 JSON 解析的逻辑
}

int main() {
    // 在这里输入文本的JSON原始字符串
    std::string jsonString = R"({"name": "John", "age": 30, "isStudent": false, "courses": ["Math", "Science"], "address": {"city": "New York", "zip": "10001"}, "nullValue": null})";
    // 令牌解析
    Tokenizer tokenizer{};
    // 语法解析
    JsonParser parser{};
    // 生成JSON对象
    JSONValue& jsonValue = parseJSON(jsonString);
}
// ...existing code...

#pragma once

#include <string>
#include <iostream>
#include <variant>
#include <vector>
#include <map>
#include <memory>
#include "JSONValue.h"

// 这里是JOSN字符串的解析器
// 1.JSON字符串预处理（消除空格，换行等不需要的内容）
// 2.将JSON字符串解析为JOSN对象并返回

class JSONparser
{
private:
    std::string m_json; // 预处理后的字符串
    size_t m_pos;
    size_t m_length;

public:
    JSONparser(std::string& json);
    ~JSONparser() = default;

    // 预处理字符串消除空格，换行等不需要的内容（并且我们后续会在这里加入识别错误的能力，保证进入parse_JSON的字符串都是符合JSON数据格式的）
    // std::string& preprocess_JSON(const std::string& jsonStr);

    // 解析JSON字符串并返回JSON对象 使用递归实现
    std::unique_ptr<JSONValue> parse_JSON();

    // 解析函数
    std::unique_ptr<JSONObject> parse_Object();
    std::unique_ptr<JSONArray> parse_Array();
    std::unique_ptr<JSONBoolean> parse_Boolean();
    std::unique_ptr<JSONNumber> parse_Number();
    std::unique_ptr<JSONString> parse_String();
    std::unique_ptr<JSONNull> parse_Null();

    // 辅助函数
    char current_char() const; // 返回当前字符
    void next_char(); // 移动到下一个字符
    void skip_whitespace(); // 跳过空白字符

};

#pragma once

#include <string>
#include <vector>
#include <iostream>

// Tokenizer.h 是令牌分析器的头文件,任务就是根据令牌构建JSON字符串然后传递给Parser(语法解析器去分析)
//然后语法解析器根据令牌返回的JSON字符串创建相应的JSON对象
class Tokenizer
{
private:
    enum class JSONType {
        JSON_Null,  // 空值
        JSON_Boolean,  // 布尔值
        JSON_Number,  // 数值
        JSON_String,  // 字符串
        JSON_Array,  // 数组
        JSON_Object  // 对象
    };
    std::string jsonString; // 存储原始 JSON 字符串
    std::map<JSONType , std::string> json_object_string;
    //定义令牌类型：BEGIN_OBJ（{）、END_OBJ（}）、BEGIN_ARR（[）、END_ARR（]）、COLON（:）、COMMA（,）、STRING（字符串值）、NUMBER（数字值）、BOOL（true/false）、NULL。
    //格式 BEGIN_OBJ ： "{"
    std::map<std::string , std::string> token_map = {
        {"BEGIN_OBJ", "{"},
        {"END_OBJ", "}"},
        {"BEGIN_ARR", "["},
        {"END_ARR", "]"},
        {"COLON", ":"},
        {"COMMA", ","},
        {"NAME" , "\""},
    };

public:
    Tokenizer(std::string& jsonString);
    ~Tokenizer() = default;  // 默认析构函数

    void tokenize(); // 令牌解析函数

    std::vector<std::string> get_json_object_string() const; // 获取 JSON 对象字符串数组(按值返回)

};

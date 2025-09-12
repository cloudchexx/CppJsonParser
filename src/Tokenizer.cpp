// 实现Tokenizer类
#include "Tokenizer.h"

// 构造函数
Tokenizer::Tokenizer(std::string& jsonString)
: jsonString{std::move(jsonString)} // 使用传入的 JSON 字符串初始化成员变量
{
    std::cout << "We create a Tokenizer" << std::endl;
}

// 令牌解析函数
void Tokenizer::tokenize() 
{

    //定义令牌类型：BEGIN_OBJ（{）、END_OBJ（}）、BEGIN_ARR（[）、END_ARR（]）、COLON（:）、COMMA（,）、STRING（字符串值）、NUMBER（数字值）、BOOL（true/false）、NULL。

    // 这里应该实现 JSON 令牌解析的逻辑
    
    //解析原始字符串，分割成一段一段的JSON_object字符串数组
    
    //将分割好的JSON_object字符串放入json_object_string数组中


}

#include "JSONparser.h"

JSONparser::JSONparser(std::string& json)
: m_json{std::move(json)}
, m_pos{static_cast<size_t>(0)}
{
    m_length = m_json.length();
}

// 预处理字符串消除空格，换行等不需要的内容（并且我们后续会在这里加入识别错误的能力，保证进入parse_JSON的字符串都是符合JSON数据格式的）
// std::string& JSONparser::preprocess_JSON(const std::string& jsonStr){
//     std::string a = "";
//     return a;
// }

// 解析JSON字符串并返回JSON对象 使用递归实现
std::unique_ptr<JSONValue> JSONparser::parse_JSON(){
    // 这里应该实现 JSON 解析的逻辑
    skip_whitespace();
    if(m_pos >= m_length) // 到了字符串的末尾了
    {
        std::cout<<"here";
        // throw "pppp";
        return nullptr;
    }

    switch (current_char())
    {
    case '{':
        try{
        return parse_Object();
        }
        catch(...){
            std::cout<<"object";
        }
    case '[':
        try{
        return parse_Array();
        }
        catch(...){
            // std::cout<<"array";
        }
    case '\"':
        try{
        return parse_String();
        }
        catch(...){
            std::cout<<"string";
        }
    case 't':
    case 'f':
        try{
        return parse_Boolean();
        }
        catch(...){
            std::cout<<"boolean";
        }
    case 'n':
        try{
        return parse_Null();
        }
        catch(...){
            std::cout<<"null";
        }
    default:
        try{
        return parse_Number();
        }
        catch(...){
            std::cout<<"number";
        }
    }
    return nullptr;
}

// 实现解析函数
std::unique_ptr<JSONBoolean> JSONparser::parse_Boolean(){
    if(m_json.substr(m_pos , static_cast<size_t>(4)) == "true") // 截取了true
    {
        m_pos += 4;
        return std::make_unique<JSONBoolean>(true);
    }
    else if (m_json.substr(m_pos , static_cast<size_t>(5)) == "false") // 截取了false
    {
        m_pos += 5;
        return std::make_unique<JSONBoolean>(false);
    }
    throw "布尔值对象错误";
}
std::unique_ptr<JSONNull> JSONparser::parse_Null(){
    if(m_json.substr(m_pos , static_cast<size_t>(4)) == "null") // 截取了null
    {
        m_pos += 4;
        return std::make_unique<JSONNull>();
    }
    throw "null对象错误";
}
std::unique_ptr<JSONNumber> JSONparser::parse_Number(){
    std::string num{""};
    if(current_char() == '-')
    {
        num += current_char();
        next_char();
    }
    while(isdigit(current_char())){
        num += current_char();
        next_char();
    }
    if(current_char() == '.') // 小数点
    {
        num += current_char();
        next_char();
        while(isdigit(current_char())){
            num += current_char();
            next_char();
        }
    }
    // std::cout<<num;
    if(!num.empty()) return std::make_unique<JSONNumber>(std::stod(num));
    else std::cout<<"number is wrong";
}
std::unique_ptr<JSONString> JSONparser::parse_String(){
    std::string str{""};
    if(current_char() == '\"') next_char();
    while (current_char() != '\"')
    {
        str += current_char();
        next_char();
    }
    next_char(); // 到了末尾"也排除就好
    if(!str.empty()) return std::make_unique<JSONString>(str);
    else throw "字符串对象错误";
}
std::unique_ptr<JSONObject> JSONparser::parse_Object(){
    if(current_char() == '{')
    {
        next_char(); // 注意字符对齐
        std::map<std::string , std::unique_ptr<JSONValue>> object_map;
        while(1)
        {
            {
                m_pos -= 1;
                if(current_char() == '}') break;
                m_pos += 1;
            }
            if(current_char() == ',') next_char();

            std::string str_key{""};

            skip_whitespace();  // 跳过空白传
            // 处理key值（字符串）
            if(current_char() == '\"')
            {
                if(current_char() == '\"') next_char();
                while (current_char() != '\"')
                {
                    str_key += current_char();
                    next_char();
                }
                next_char(); // 到了末尾"也排除就好
                if(str_key.empty()) throw "Object对象错误";
            }

            // std::cout<<str_key<<std::endl;

            skip_whitespace();
            if(current_char() != ':') throw "Object对象错误";
            else next_char();
            skip_whitespace();
            // 处理值
            auto json_value =  parse_JSON();
            if(json_value == nullptr) break;

            next_char();

            object_map.insert(std::make_pair(str_key , std::move(json_value)));
        }
        next_char();
        return std::make_unique<JSONObject>(object_map);
    }
    else
        throw "Object对象错误";
}
std::unique_ptr<JSONArray> JSONparser::parse_Array(){
    if(current_char() == '[')
    {
        next_char();
        std::vector<std::unique_ptr<JSONValue>> arr{};
        while(current_char() != ']')
        {
            // 处理前面的不需要的字符
            skip_whitespace();
            if(current_char() == ',') next_char(); // 遇见这个就next就好了
            skip_whitespace();

            // 直接处理值
            auto json_value = parse_JSON();
            arr.push_back(std::move(json_value));
        }
        next_char();
        return std::make_unique<JSONArray>(arr);
    }
    else
        throw "Array对象错误";
}



// 实现辅助函数
char JSONparser::current_char() const // 返回当前字符
{
    return (m_pos < m_length)?m_json[m_pos]:'\0';
}
void JSONparser::next_char()
{
    if(m_pos < m_length)
        m_pos++;
} 
void JSONparser::skip_whitespace()
{
    while(m_pos < m_length && isspace(static_cast<int>(current_char()))){
        next_char();
    }
}
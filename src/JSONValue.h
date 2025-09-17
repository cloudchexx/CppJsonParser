#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <memory>
#include <variant>

enum JSONType {
    JSON_Void,  // 无效值
    JSON_Null,  // 空值
    JSON_Boolean,  // 布尔值
    JSON_Number,  // 数值
    JSON_String,  // 字符串
    JSON_Array,  // 数组
    JSON_Object  // 对象
};

// 前向声明，供Array和Object使用
class JSONValue;

// 定义数组和对象的元素类型
// using JSONArray = std::vector<std::unique_ptr<JSONValue>>;
// using JSONObject = std::map<std::string, std::unique_ptr<JSONValue>>;

// 定义value的可能类型（variant支持的类型列表）
using JSONVariant = std::variant<
    // 初始化对象时的默认值
    
    std::monostate,   // 对应Null（占位用）
    bool,             // 对应Bool
    double,           // 对应Number（统一存储整数和浮点数）
    std::string,      // 对应String
    std::vector<std::unique_ptr<JSONValue>>,        // 对应Array
    std::map<std::string , std::unique_ptr<JSONValue>>        // 对应Object
>;

// JSON数据的基类
class JSONValue
{
private:
    JSONVariant m_value; // JSON数据的值
    JSONType m_type{JSONType::JSON_Void}; // JSON数据的类型
public:
    JSONValue(JSONVariant value , JSONType type); // 默认构造函数
    ~JSONValue() = default;  // 确保派生类对象正确析构

    // void setvalueandtype(JSONVariant val, JSONType t); // 设置 JSON数据的值和类型

    JSONType gettype() const; // 返回 JSON数据的类型

    const JSONVariant& getValue() const; // 返回 JSON数据的值

    //重载输出运算符，方便调试
    friend std::ostream& operator<<(std::ostream& os, const JSONValue& json);
};


// 空值类JSONNull
class JSONNull : public JSONValue
{
public:
    JSONNull(JSONVariant value  = std::monostate{}, JSONType type = JSON_Null); // 构造函数
};

// 布尔值类JSONBoolean
class JSONBoolean : public JSONValue
{
public:
    JSONBoolean(bool value,JSONType type = JSON_Boolean); // 构造函数，接受一个布尔值
};

// 数值类JSONNumber
class JSONNumber : public JSONValue
{
public:
    JSONNumber(double value , JSONType type = JSON_Number); // 构造函数，接受一个数值
};

// 字符串类JSONString
class JSONString : public JSONValue
{
public:
    JSONString(const std::string& value , JSONType type = JSON_String); // 构造函数，接受一个字符串
};

// 数组类JSONArray
class JSONArray : public JSONValue
{
public:
    JSONArray(std::vector<std::unique_ptr<JSONValue>>& value , JSONType type = JSON_Array); // 构造函数，接受一个数组
    void append(std::unique_ptr<JSONValue> value); // 向数组也就是（value值）中添加元素
    JSONValue& operator[] (int index); // 返回对应的元素的引用
};

// 对象类JSONObject
class JSONObject : public JSONValue
{
public:
    JSONObject(std::map<std::string , std::unique_ptr<JSONValue>>& value , JSONType type = JSON_Object); // 构造函数，接受一个对象
    void insert(const std::string& key, std::unique_ptr<JSONValue> value); // 向对象也就是（value值）中添加键值对
    JSONValue& operator [](const std::string& key_str);  // 根据键值查找对象
};

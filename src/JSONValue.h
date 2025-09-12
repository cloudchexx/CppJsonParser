#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <memory>

// JSON数据的基类
class JSONValue
{

private:
    // 私有成员变量和方法
    std::string JsonString; // 存储原始 JSON 字符串

public:

    // JSON 值的类型枚举
    enum class JSONType {
        JSON_Null,  // 空值
        JSON_Boolean,  // 布尔值
        JSON_Number,  // 数值
        JSON_String,  // 字符串
        JSON_Array,  // 数组
        JSON_Object  // 对象
    };

    JSONValue(std::string& json); // 默认构造函数
    virtual ~JSONValue() = default;

    std::string_view get_JSONString() const; // 获取 JSON 字符串

    // 需要一个自行判断类别的接口，返回值可以是一个枚举类型
    virtual JSONType getType() const; // 获取 JSON 值的类型,虚函数类型，需要有具体的JSON类实现判断方法

    // 需要一个接口返回具体的值
    virtual std::unique_ptr<JSONValue> asValue_of_JSON() const; // 将 JSON 值转换为布尔值
};

// JSON 空值类，继承自 JSONValue
class JSON_Null : public JSONValue
{
public:
    JSON_Null(std::string& json); // 构造函数 构造JSON_Null对象
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
};

// JSON 布尔值类，继承自 JSONValue
class JSON_Boolean : public JSONValue
{
private:
    bool value; // 存储布尔值
public:
    JSON_Boolean(std::string& json ,bool val); // 构造函数 构造JSON_Boolean对象
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
};

// JSON 数值类，继承自 JSONValue
class JSON_Number : public JSONValue
{
private:
    double value; // 存储数值
public:
    JSON_Number(std::string& json , double val); // 构造函数 构造JSON_Number对象
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
};

// JSON 字符串类，继承自 JSONValue
class JSON_String : public JSONValue
{
private:
    std::string value; // 存储字符串
public:
    JSON_String(const std::string& val); // 构造函数 构造JSON_String对象
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
};

// JSON 数组类，继承自 JSONValue
class JSON_Array : public JSONValue
{
private:
    std::vector<std::unique_ptr<JSONValue>> values; // 存储JSON值元素的指针
public:
    JSON_Array(); // 构造函数 构造JSON_Array对象
    bool addValue(std::unique_ptr<JSONValue> val); // 添加 JSON 值元素
    bool removeValue(int index); // 根据下标移除 JSON 值元素
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
    std::unique_ptr<JSONValue> operator[] (int index); // 重载下标运算符，根据下标访问数组元素
};

// JSON 对象类，继承自 JSONValue
class JSON_Object : public JSONValue
{
private:
    std::map<std::string, std::unique_ptr<JSONValue>> members; // 存储键值对，值为 JSON 值的指针
public:
    JSON_Object(); // 构造函数 构造JSON_Object对象
    bool addMember(const std::string& key, std::unique_ptr<JSONValue> val); // 添加键值对
    bool removeMember(const std::string& key); // 根据键移除键值对
    JSONType getType() const override; // 获取 JSON 值的类型
    std::unique_ptr<JSONValue> asValue_of_JSON() const override;
    std::unique_ptr<JSONValue> operator[] (const std::string& key); // 重载下标运算符，根据键访问对象成员
};

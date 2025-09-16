#include "JSONValue.h"

// JSONValue类的实现
JSONValue::JSONValue(){}
void JSONValue::setvalueandtype(JSONVariant val, JSONType t) {
    value = std::move(val);
    type = t;
}
JSONType JSONValue::gettype() const {
    return type;
}
const JSONVariant& JSONValue::getValue() const {
    return value;
}
std::ostream& operator<<(std::ostream& os, const JSONValue& json){
    switch (json.gettype()) {
        case JSONType::JSON_Null:
            os << "null";
            break;
        case JSONType::JSON_Boolean:
            os << (std::get<bool>(json.getValue()) ? "true" : "false");
            break;
        case JSONType::JSON_Number:
            os << std::get<double>(json.getValue());
            break;
        case JSONType::JSON_String:
            os << "\"" << std::get<std::string>(json.getValue()) << "\"";
            break;
        case JSONType::JSON_Array: {
            os << "[";
            const auto& arr = std::get<std::vector<std::unique_ptr<JSONValue>>>(json.getValue());
            for (size_t i = 0; i < arr.size(); ++i) {
                if (i > 0) os << ", ";
                os << *(arr[i]);
            }
            os << "]";
            break;
        }
        case JSONType::JSON_Object: {
            os << "{";
            const auto& obj = std::get<std::map<std::string , std::unique_ptr<JSONValue>>>(json.getValue());
            size_t count = 0;
            for (const auto& [key, val] : obj) {
                if (count++ > 0) os << ", ";
                os << "\"" << key << "\": " << *val;
            }
            os << "}";
            break;
        }
        default:
            os << "undefined";
    }
    return os;
}


// JSONBoolean类的实现
JSONBoolean::JSONBoolean(bool b)
{
    setvalueandtype(b, JSONType::JSON_Boolean);
}
// JSONNumber类的实现
JSONNumber::JSONNumber(double num)
{
    setvalueandtype(num, JSONType::JSON_Number);
}
// JSONString类的实现
JSONString::JSONString(const std::string& str)
{
    setvalueandtype(str, JSONType::JSON_String);
}
// JOSONArray类的实现
JSONArray::JSONArray(std::vector<std::unique_ptr<JSONValue>>& arr)
{
    setvalueandtype(std::move(arr), JSONType::JSON_Array);
}
void JSONArray::append(std::unique_ptr<JSONValue> value) {
    if (gettype() == JSONType::JSON_Array) {
        auto& arr = std::get<std::vector<std::unique_ptr<JSONValue>>>(const_cast<JSONVariant&>(getValue()));
        arr.push_back(std::move(value));
    }
}
// JSONObject类的实现
JSONObject::JSONObject(std::map<std::string , std::unique_ptr<JSONValue>>& obj)
{
    setvalueandtype(std::move(obj), JSONType::JSON_Object);
}
void JSONObject::insert(const std::string& key, std::unique_ptr<JSONValue> value) {
    if (gettype() == JSONType::JSON_Object) {
        auto& obj = std::get<std::map<std::string , std::unique_ptr<JSONValue>>>(const_cast<JSONVariant&>(getValue()));
        obj[key] = std::move(value);
    }
}
// JSONNull类的实现
JSONNull::JSONNull()
{
    setvalueandtype(std::monostate{}, JSONType::JSON_Null);
}
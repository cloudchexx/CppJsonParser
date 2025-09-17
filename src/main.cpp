#include "JSONparser.h"
// #include "JSONValue.h"
#include <iostream>

int main() {
    try{
        std::string jsonStr_1 = R"({"name": "Alice", "age": 25, "isStudent": false, "scores": [88.5, 92, 79], "address": null,"ppp":{"hhh":9,"ttt":true}})";
        std::string jsonStr_2 = R"(["name" , 19 , true , null , ["hhh",55] , {"sex":"boy" , "yyy":12}])";
        JSONparser parser_1{jsonStr_1};
        JSONparser parser_2{jsonStr_2};
        auto jsonValue_1 = parser_1.parse_JSON();
        auto jsonValue_2 = parser_2.parse_JSON();
        std::cout << *jsonValue_1 << std::endl;
        std::cout << *jsonValue_2 << std::endl;

        if(jsonValue_1->gettype() == JSON_Object)
        {
            JSONObject& obj = *(static_cast<JSONObject*>(jsonValue_1.get()));  // 变成Obj引用
            JSONArray& arr = static_cast<JSONArray&>(obj["scores"]);
            std::cout << arr << std::endl;
            arr.append(std::make_unique<JSONString>("good boy"));
            std::cout << arr << std::endl;
        }

        // 测试Array重载运算符
        JSONArray* arr{nullptr};
        if(jsonValue_2->gettype() == JSON_Array)
        {
            JSONArray& arr = *(static_cast<JSONArray*>(jsonValue_2.get()));
            JSONValue& a = arr[4];
            JSONArray& b = static_cast<JSONArray&>(a);
            std::cout << b << std::endl;
            b.append(std::make_unique<JSONBoolean>(true));
            std::cout << b << std::endl;
        }

        // parser.preprocess_JSON(jsonStr); // 预处理（当前实现未做实际处理）

        // 创建一些JSON对象
        JSONBoolean boolVal(true);
        JSONNumber numVal(42.0);
        JSONString strVal("Hello, World!");
        std::vector<std::unique_ptr<JSONValue>> arrVal;
        arrVal.push_back(std::make_unique<JSONNumber>(1.0));
        arrVal.push_back(std::make_unique<JSONString>("Two"));
        JSONArray jsonArray(arrVal);
        std::map<std::string, std::unique_ptr<JSONValue>> objVal;
        objVal["key1"] = std::make_unique<JSONBoolean>(false);
        objVal["key2"] = std::make_unique<JSONNumber>(3.14);
        JSONObject jsonObject(objVal);
        // // 输出这些对象
        // std::cout << boolVal << std::endl;
        // std::cout << numVal << std::endl;
        // std::cout << strVal << std::endl;
        // std::cout << jsonArray << std::endl;
        // std::cout << jsonObject << std::endl;
    }
    catch(char * e){
        std::cout << "wrong is " << e << std::endl;
    }
    return 0;
}
#include "JSONparser.h"
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

        // parser.preprocess_JSON(jsonStr); // 预处理（当前实现未做实际处理）
    }
    catch(char * e){
        std::cout << "wrong is " << e << std::endl;
    }
    return 0;
}
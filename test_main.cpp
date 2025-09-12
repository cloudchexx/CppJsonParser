#include <iostream>
#include <string>
#include "JsonValue.h"
#include <vector>
#include <memory>


int main() {

    std::string json = R"({"name": "John", "age": 30, "isStudent": false, "courses": ["Math", "Science"], "address": {"city": "New York", "zip": "10001"}})";

    std::vector<std::unique_ptr<JSONValue>> jsonValues_stack;
    std::vector<char&> char_stack;

    // 这里的逻辑只能对正常的JSON字符串进行解析
    // 如果有特殊的情况需要进行一些预处理

    // 例如： "name {} [ , : "  例如字符串对象里出现这些令牌字符就会解析错误

    for(auto& ch : json) {
        char_stack.push_back(ch);  // 将字符逐个压入栈中
        int type = is_type(jsonValues_stack.back().gettype()); // 获取当前栈顶对象的类型 1是Object 2是Array
        // 根据对象栈栈顶对象的类型进行不同的处理
        // 例如如果是Object类型，就需要处理键值对
        // 如果是Array类型，就只需要处理值就行
        if(ch == '{'){
            JSON_Object json_object();  // 创建一个JSON_Object对象
            // 这里需要将这个对象先传给上一个对象，先不着急入栈
            jsonValues_stack.back().add(json_object);
            jsonValues_stack.push_back(std::make_unique<JSON_Object>(json_object)); // 将对象指针压入栈中
        }
        if(ch == '['){
            JSON_Array json_array();  // 创建一个JSON_Array对象
            // 这里需要将这个对象先传给上一个对象，先不着急入栈
            jsonValues_stack.back().add(json_array);
            jsonValues_stack.push_back(std::make_unique<JSON_Array>(json_array)); // 将对象指针压入栈中
        }
        if(ch == '}' || ch == ']'){
            // 这个对象的内容已经结束，可以进行一些收尾工作
            jsonValues_stack.pop_back(); // 将对象指针弹出栈
            char_stack.pop_back(); // 将字符弹出栈
        }

        //
        if(type == 1){ // Object类型
            // 这里需要处理键值对
            if(ch == ':'){
                // 说明前面已经读完了一个键，可以进行一些处理
                // 生成键值
            }
            if(ch == ','){
                // 说明前面已经读完了一个键值对，可以进行一些处理
                // 加入键值对
            }
        }
        if(type == 2){ // Array类型
            // 这里需要处理值
            if(ch == ','){
                // 说明前面已经读完了一个值，可以进行一些处理
                // 插入值
            }
        }

    }
    jsonValues_stack.pop_back(); // 弹出最后一个对象
    if(!jsonValues_stack.empty()){
        std::cerr << "Error: JSON parsing did not complete successfully." << std::endl;
        return -1; // 返回错误码
    }


    return 0;
}

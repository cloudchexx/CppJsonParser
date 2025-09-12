# CppJsonParser

这是一个用于实现 C++ JSON 解析器的工程模板。

## 目录结构建议

- src/main.cpp         // 程序入口
- src/json_parser.h    // JSON解析器头文件
- src/json_parser.cpp  // JSON解析器实现

## 构建方法

1. 安装 CMake 和支持 C++17 的编译器（如 g++, clang, MSVC）。
2. 在项目根目录下执行：
   ```powershell
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. 生成的可执行文件在 build 目录下。

## 工作流
1. 输入原始JSON串到令牌分析器
2. 分割成一段一段的JSON_object字符串数组
3. 将JSON_object字符串数组放入Parser（语法解析器）中生成相应的JSON对象
4. 注意，最小单元的JSON对象是null，bool，number之类的，array以及object的JSON对象不是最小单元，所以还将其JSON_object字符串放入令牌解析器中解析，再放入Parser中生成JSON对象，知道最后一个最小单元被完成（这个过程是递归实现）
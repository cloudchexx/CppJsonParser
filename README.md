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
我们需要确认工作流，使用两个栈来实现解析JSON对象
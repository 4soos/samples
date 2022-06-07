# sylar server 

## 开发环境
教程环境：
- gcc 9.1
- centos 7

实际环境：
- gcc 11.2
- manjaro

## 项目结构
教程：
bin
build
cmake
CMakeLists.txt
Makefile
sylar
tests

实际：
├── bin
├── build
├── cmake
├── CMakeLists.txt
├── Makefile
├── notes.md
├── sylar
└── tests


## 日志系统

1) 类关系

```
    Logger
        |
        |------ Formatter 
        |
    Appender
```


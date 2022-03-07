# 单例

在单例类里,又分为了懒汉式和饿汉式,它们的区别在于创建实例的时间不同:

* 懒汉式 : 指代码运行后,实例并不存在,只有当需要时,才去创建实例(适用于单线程)
* 饿汉式 : 指代码一运行,实例已经存在,当时需要时,直接去调用即可(适用于多线程)

具体实现:

1. 将构造函数的访问属性设置为private,
2. 提供一个GetInstance()静态成员函数,只能供用户访问唯一一个实例.
3. 定义一个静态成员指针,用来供用户获取
4. 重载 (=)赋值操作符以及拷贝构造函数,并设为private, 避免对象间拷贝,复制.


初探单例类-懒汉式:
```cpp
#include <iostream>
using namespace std; 

class CSingleton
{
private:
       static CSingleton* m_pInstance;

       CSingleton()         //构造函数为private
       {
       } 

       CSingleton& operator = (const CSingleton& t);
       CSingleton(const CSingleton &);
public:
       static CSingleton* getInstance()
       {
              if(m_pInstance==NULL)
                     m_pInstance= new CSingleton(); 
           
               return m_pInstance;
       }

       void print()
       {
           cout<<this<<endl;      
       }
};

CSingleton* CSingleton::m_pInstance = NULL;

int main()
{
       CSingleton *p1=CSingleton::getInstance();
       CSingleton *p2=CSingleton::getInstance(); 
       CSingleton *p3=CSingleton::getInstance();

       p1->print();
       p2->print();
       p3->print();

　　　　return 0;
}
```
运行打印:
```bash
0x6e2d18
0x6e2d18
0x6e2d18
```
从打印结果可以看出,该指针对象指向的都是同一个地址,实现了一个类最多只能有一个实例(instance)存在.

注意:由于实例(instance),在系统生命期中,都是存在的,所以只要系统还在运行,就不需要delete

上面的懒汉式如果在多线程情况下 ,多个Csingleton指针对象同时调用getInstance()成员函数时,由于m_pInstance = NULL,就会创建多个实例出来.

所以,在多线程情况下,需要使用饿汉实现

代码如下:

```cpp
class CSingleton
{
private:

       static CSingleton* m_pInstance;

        CSingleton()         //构造函数为private
       {
       }             

       CSingleton& operator = (const CSingleton& t);
       CSingleton(const CSingleton &); 

public:
       static CSingleton* getInstance()
       {  
               return m_pInstance;
       }
};

CSingleton* CSingleton::m_pInstance = new CSingleton;  
```








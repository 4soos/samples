#include <iostream>
#include <thread>


/**
由于实例(instance),在系统生命期中,都是存在的,所以只要系统还在运行,就不需要delete

上面的懒汉式如果在多线程情况下 ,多个Csingleton指针对象同时调用getInstance()成员函数时,

由于m_pInstance = NULL,就会创建多个实例出来.

所以,在多线程情况下,需要使用饿汉实现
*/

class MSingleton {
private:
    static MSingleton * instance;
    MSingleton() { }

    MSingleton& operator = (const MSingleton& t);
    MSingleton(const MSingleton &);

public:
    static MSingleton* getInstance() {
        return instance;
    }

};

MSingleton* MSingleton::instance = new MSingleton;


int main() {

}

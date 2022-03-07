#ifndef __SINGLETON_H
#define __SINGLETON_H

template <typename T>
class TSingleton
{
private:
    static T* m_instance;

    TSingleton() { }       //构造函数为private
           
        
public:
    static T* getInstance() {   
        return m_instance;
    }
};

template <typename T>
T* TSingleton<T>::m_instance = new T;

#endif

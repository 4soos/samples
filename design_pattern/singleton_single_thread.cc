#include <iostream>
#include <thread>

using namespace std;

class CSingleton {

private:
    static CSingleton* instance;
    
    CSingleton() {  }

    CSingleton& operator= (const CSingleton & t);

    CSingleton(const CSingleton &);

public:

    static CSingleton* getInstance() {
        if (instance == nullptr) instance = new CSingleton();

        return instance;
    }

    void print() {
        cout << this << endl;
    }

};


CSingleton* CSingleton::instance = nullptr;

int main() {
    CSingleton *p1 = CSingleton::getInstance();
    CSingleton *p2 = CSingleton::getInstance();
    CSingleton *p3 = CSingleton::getInstance();

    std::thread t1( [] { 
            CSingleton *p4 = CSingleton::getInstance();
            p4->print();
        });

    p1->print();
    p2->print();
    p3->print();
    t1.join();

    return 0;
}




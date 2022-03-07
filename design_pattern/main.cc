#include <iostream>
#include <string>
#include "singleton.h"

using namespace std;

class test {
    
    friend class TSingleton<test>; //声明Test的友元为单例类模板

private:
    string mstr;
    
    test(): mstr("test") { }

    test& operator= (const test& t);

    test(const test&);

public:
    void set_mstr(string s) {
        mstr = s;
    }

    void print() {
        cout << "mstr = " << mstr << endl;
        cout << "this = " << this << endl;
    }

};

int main() {
    test *pt1 = TSingleton<test>::getInstance();
    test *pt2 = TSingleton<test>::getInstance();

    pt1->print();
    pt2->print();

    pt1->set_mstr("****************");
    pt2->print();

    return 0;
}

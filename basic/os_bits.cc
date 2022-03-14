#include <iostream>

using namespace std;

int main() {
    int a = ~0;
    
    cout<< "a: " << a << endl;

    if(a > 65536) {
        cout<<"32 bit"<<endl;
    
    } else {
        cout<<"16 bit"<<endl;
    }
    return 0;
}



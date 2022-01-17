
#include <cstring>

class dynamic_array {
    int size;
    int *ptr;

public:
    dynamic_array(int s = 0): size(s) {
        if ( s== 0) ptr == nullptr;
        else ptr = new int[s];
        
    }

    dynamic_array(dynamic_array & a) { //复制构造
        if (!a.ptr) {
            ptr = nullptr;
            size = 0;
            return;
        }
        ptr = new int[a.size];
        memcpy(ptr, a.ptr, sizeof(int) * a.size);
        size = a.size;
    }

    ~dynamic_array() {
        if (ptr) delete []ptr;
    }

    void push_back(int v) {
        if (ptr) {
            int * ptr_tmp_ = new int[size + 1];
            memcpy(ptr_tmp_, ptr, sizeof(int) * size);
            delete []ptr;
            ptr = ptr_tmp_;
        }
        else ptr = new int[1];

        ptr[size++] = v;
    }

    dynamic_array & operator=(const dynamic_array & a) {
        if (ptr = a.ptr) return *this;

        if (size < a.size) {
            if (ptr) delete []ptr;

            ptr = new int[a.size];

        }
        memcpy(ptr, a.ptr, sizeof(int)*a.size);
        size = a.size;
        return *this;
    }

    int len() { return size; }

};

















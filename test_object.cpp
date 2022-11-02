#include <iostream>

class C {
public:
    int* ptr = nullptr;
    C(int v) {
        ptr = new int(v);
        // std::cout << "C(int v)" << " *ptr=" << *ptr << std::endl;
    }
    ~C() {
        // std::cout << "~C()" << " *ptr=" << *ptr << std::endl;
        delete ptr;
    }

    C(const C& other) {
        ptr = new int;
        *ptr = *other.ptr;
        // std::cout << "C(const C& other)" << " *ptr=" << *ptr << std::endl;
    }

    C& operator=(const C& other) {
        if (this == &other) {return *this;}
        ptr = new int(*other.ptr);
        // std::cout << "C& operator=(const C& other)" << " *ptr=" << *ptr << std::endl;
        return *this;
    }
};
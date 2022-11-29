#pragma once

#include <iostream>

class D {
public:
    static int s_instance_counter;
    static int s_ctor_counter;
    static int s_copy_ctor_counter;
    static int s_operator_assignment_counter;

    int* m_ptr = nullptr;

    D(int v) : m_ptr(new int(v)) {
        // std::cout << "D(int v)" << " *ptr=" << *m_ptr << std::endl;
        ++s_ctor_counter;
        ++s_instance_counter;
    }
    ~D() {
        // std::cout << "~D()" << " *ptr=" << *m_ptr << std::endl;
        delete m_ptr;
        --s_instance_counter;
    }
    D(const D& other) {
        m_ptr = new int;
        *m_ptr = *other.m_ptr;
        // std::cout << "D(const D& other)" << " *ptr=" << *m_ptr << std::endl;
        // std::cout << "copy" << std::endl;
        ++s_copy_ctor_counter;
        ++s_instance_counter;
    }
    D& operator=(const D& other) {
        // std::cout << "D& operator=(const D& other)" << std::endl;
        // std::cout << "operator=" << std::endl;
        ++s_operator_assignment_counter;
        if (this == &other) {return *this;}
        m_ptr = new int(*other.m_ptr);
        // std::cout << "D& operator=(const D& other)" << " *ptr=" << *m_ptr << std::endl;
        return *this;
    }

    static void print_instance_counter() {
        std::cout << "D::s_instance_counter: " << s_instance_counter << std::endl;
    }
    static void print_counters() {
        std::cout << "D::s_instance_counter: " << s_instance_counter << "\n" <<
            "D::s_ctor_counter: " << s_ctor_counter << "\n" <<
            "D::s_copy_ctor_counter: " << s_copy_ctor_counter << "\n" <<
            "D::s_operator_assignment_counter: " << s_operator_assignment_counter << std::endl;
    }

    static int get_instance_counter() {
        return s_instance_counter;
    }
    static int get_ctor_counter() {
        return s_ctor_counter;
    }
    static int get_copy_ctor_counter() {
        return s_copy_ctor_counter;
    }
    static int get_operator_assignment_counter() {
        return s_operator_assignment_counter;
    }

    static void reset_counters() {
        s_instance_counter = 0;
        s_ctor_counter = 0;
        s_copy_ctor_counter = 0;
        s_operator_assignment_counter = 0;
    }
};
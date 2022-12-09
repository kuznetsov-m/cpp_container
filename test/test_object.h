#pragma once

#include <iostream>

class D {
public:
    static int s_instance_counter;
    static int s_ctor_counter;
    static int s_copy_ctor_counter;
    static int s_move_ctor_counter;
    static int s_copy_assignment_operator_counter;
    static int s_move_assignment_operator_counter;

    int* m_value = nullptr;

    D(int v) : m_value(new int(v)) {
        // std::cout << "D() m_value=" << *m_value << std::endl;
        ++s_ctor_counter;
        ++s_instance_counter;
    }
    ~D() {
        // std::cout << "~D() m_value=";
        // if (m_value) { std::cout << *m_value; }
        // else { std::cout << "nullptr"; }
        // std::cout << std::endl;

        delete m_value;
        --s_instance_counter;
    }
    D(const D& other) {
        m_value = new int;
        *m_value = *other.m_value;
        // std::cout << "D(const D& other)" << " *ptr=" << *m_value << std::endl;
        // std::cout << "copy" << std::endl;
        ++s_copy_ctor_counter;
        ++s_instance_counter;
    }
    D(D&& other) : m_value(other.m_value){
        // std::cout << "move" << std::endl;
        
        other.m_value = nullptr;

        ++s_move_ctor_counter;
        ++s_instance_counter;
    }
    D& operator=(const D& other) {
        // std::cout << "copy operator=" << std::endl;
        ++s_copy_assignment_operator_counter;

        if (this == &other) {return *this;}
        m_value = new int(*other.m_value);

        return *this;
    }
    D& operator=(D&& other) {
        // std::cout << "move operator=" << std::endl;
        ++s_move_assignment_operator_counter;

        if (this == &other) { return *this; }
        m_value = other.m_value;
        other.m_value = nullptr;

        return *this;
    }

    static void print_instance_counter() {
        std::cout << "D::s_instance_counter: " << s_instance_counter << std::endl;
    }
    static void print_counters() {
        std::cout << "D::s_instance_counter: " << s_instance_counter << "\n" <<
            "D::s_ctor_counter: " << s_ctor_counter << "\n" <<
            "D::s_copy_ctor_counter: " << s_copy_ctor_counter << "\n" <<
            "D::s_move_ctor_counter: " << s_move_ctor_counter << "\n" <<
            "D::s_copy_assignment_operator_counter: " << s_copy_assignment_operator_counter << "\n" <<
            "D::s_move_assignment_operator_counter: " << s_move_assignment_operator_counter << std::endl;
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
    static int get_move_ctor_counter() {
        return s_move_ctor_counter;
    }
    static int get_copy_assignment_operator_counter() {
        return s_copy_assignment_operator_counter;
    }
    static int get_move_assignment_operator_counter() {
        return s_move_assignment_operator_counter;
    }

    static void reset_counters() {
        s_instance_counter = 0;
        s_ctor_counter = 0;
        s_copy_ctor_counter = 0;
        s_move_ctor_counter = 0;
        s_copy_assignment_operator_counter = 0;
        s_move_assignment_operator_counter = 0;
    }
};
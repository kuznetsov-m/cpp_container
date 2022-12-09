#include <gtest/gtest.h>

#include <vector>

#include "vector.h"
#include "test_object.h"

// failed with win
#if defined __GNUC__

TEST(vector_custom_vs_std, push_back) {
    int count = 5;
    
    // std:

    std::vector<D> std_v;
    for (size_t i = 0; i < count; ++i) {
        std_v.push_back(i);
    }
    auto std_ctor_counter = D::get_ctor_counter();
    auto std_copy_ctor_counter = D::get_copy_ctor_counter();
    auto std_move_ctor_counter = D::get_move_ctor_counter();
    auto std_copy_assignment_operator_counter = D::get_copy_assignment_operator_counter();
    auto std_move_assignment_operator_counter = D::get_move_assignment_operator_counter();
    D::reset_counters();

    // custom:
    
    Vector<D> custom_v;
    for (size_t i = 0; i < count; ++i) {
        custom_v.push_back(i);
    }
    auto custom_ctor_counter = D::get_ctor_counter();
    auto custom_copy_ctor_counter = D::get_copy_ctor_counter();
    auto custom_move_ctor_counter = D::get_move_ctor_counter();
    auto custom_copy_assignment_operator_counter = D::get_copy_assignment_operator_counter();
    auto custom_move_assignment_operator_counter = D::get_move_assignment_operator_counter();

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());

    ASSERT_EQ(std_ctor_counter, custom_ctor_counter);
    ASSERT_EQ(std_copy_ctor_counter, custom_copy_ctor_counter);
    ASSERT_EQ(std_move_ctor_counter, custom_move_ctor_counter);
    ASSERT_EQ(std_copy_assignment_operator_counter, custom_copy_assignment_operator_counter);
    ASSERT_EQ(std_move_assignment_operator_counter, custom_move_assignment_operator_counter);
}

TEST(vector_custom_vs_std, clear) {
    int count = 5;
    
    std::vector<D> std_v;
    Vector<D> custom_v;
    for (size_t i = 0; i < count; ++i) {
        std_v.push_back(i);
        custom_v.push_back(i);
    }

    std_v.clear();
    custom_v.clear();

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());
}

TEST(vector_custom_vs_std, insert_to_begin) {
    int count = 5;
    
    std::vector<D> std_v;
    Vector<D> custom_v;
    for (size_t i = 0; i < count; ++i) {
        std_v.push_back(i);
        custom_v.push_back(i);
    }

    std_v.insert(std_v.begin(), 0);
    custom_v.insert(0, 0);

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());

    std_v.clear();
    custom_v.clear();
}

#endif // __GNUC__
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
    auto std_operator_assignment_counter = D::get_operator_assignment_counter();
    D::reset_counters();

    // custom:
    
    Vector<D> custom_v;
    for (size_t i = 0; i < count; ++i) {
        custom_v.push_back(i);
    }
    auto custom_ctor_counter = D::get_ctor_counter();
    auto custom_copy_ctor_counter = D::get_copy_ctor_counter();
    auto custom_operator_assignment_counter = D::get_operator_assignment_counter();

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());

    ASSERT_EQ(std_ctor_counter, custom_ctor_counter);
    ASSERT_EQ(std_copy_ctor_counter, custom_copy_ctor_counter);
    ASSERT_EQ(std_operator_assignment_counter, custom_operator_assignment_counter);
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

#endif // __GNUC__
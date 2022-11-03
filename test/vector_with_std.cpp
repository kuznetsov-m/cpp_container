#include <gtest/gtest.h>

#include <vector>

#include "vector.h"
#include "test_object.h"

// failed with win
#if defined __GNUC__

TEST(vector_custom_vs_std, push_back) {
    int count = 5;
    
    std::vector<C> std_v;
    Vector<C> custom_v;
    for (size_t i = 0; i < count; ++i) {
        std_v.push_back(i);
        custom_v.push_back(i);
    }

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());
}

TEST(vector_custom_vs_std, clear) {
    int count = 5;
    
    std::vector<C> std_v;
    Vector<C> custom_v;
    for (size_t i = 0; i < count; ++i) {
        std_v.push_back(i);
        custom_v.push_back(i);
    }

    std_v.clear();
    custom_v.clear();

    ASSERT_EQ(std_v.size(), custom_v.size());
    ASSERT_EQ(std_v.capacity(), custom_v.capacity());
}

#endif
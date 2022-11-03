#include <gtest/gtest.h>

#include "vector.h"
#include "test_object.h"

TEST(vector, constructor) {
    Vector<C> v;
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
}

TEST(vector, size) {
    Vector<C> v;
    ASSERT_EQ(v.size(), 0);

    for (size_t i = 0; i < 4; ++i) {
        v.push_back(0);
        ASSERT_EQ(v.size(), i + 1);
    }
}

TEST(vector, capacity) {
    Vector<C> v;
    ASSERT_EQ(v.capacity(), 0);

    v.push_back(0);
    ASSERT_EQ(v.capacity(), 1);
    v.push_back(1);
    ASSERT_EQ(v.capacity(), 2);
    v.push_back(2);
    ASSERT_EQ(v.capacity(), 4);
    v.push_back(3);
    ASSERT_EQ(v.capacity(), 4);
    v.push_back(4);
    ASSERT_EQ(v.capacity(), 8);
}
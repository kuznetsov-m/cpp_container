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

TEST(vector, operator_index) {
    Vector<C> v;
    C value(0);
    v.push_back(value);
    ASSERT_EQ(*v[0].ptr, *value.ptr);
}

TEST(vector, at) {
    Vector<C> v;
    C value(0);
    v.push_back(value);
    ASSERT_EQ(*v.at(0).ptr, *value.ptr);
}

TEST(vector, at_out_of_range) {
    Vector<C> v;
    try {
        v.at(0);
    }
    catch (const std::out_of_range& e) {
        ASSERT_EQ(strcmp(e.what(), "out_of_range"), 0);
    }
}

TEST(vector, push_back) {
    Vector<C> v;
    C value(0);
    for (int i = 0; i < v.size(); ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < v.size(); ++i) {
        ASSERT_EQ(*v.at(0).ptr, i);
    }
}

TEST(vector, front) {
    Vector<C> v;
    C value(0);
    v.push_back(value);
    v.push_back(1);
    ASSERT_EQ(*v.front().ptr, *value.ptr);
}

TEST(vector, back) {
    Vector<C> v;
    C value(1);
    v.push_back(0);
    v.push_back(value);
    ASSERT_EQ(*v.back().ptr, *(value.ptr));
}

TEST(vector, erase_1) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(0);
    ASSERT_EQ(*v.at(0).ptr, 1);
    ASSERT_EQ(*v.at(1).ptr, 2);
}

TEST(vector, erase_2) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(1);
    ASSERT_EQ(*v.at(0).ptr, 0);
    ASSERT_EQ(*v.at(1).ptr, 2);
}

TEST(vector, erase_3) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(2);
    ASSERT_EQ(*v.at(0).ptr, 0);
    ASSERT_EQ(*v.at(1).ptr, 1);
}

TEST(vector, erase_4) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(3);
    ASSERT_EQ(*v.at(0).ptr, 0);
    ASSERT_EQ(*v.at(1).ptr, 1);
    ASSERT_EQ(*v.at(2).ptr, 2);
}

TEST(vector, pop_back_1) {
    Vector<C> v;
    v.pop_back();
    ASSERT_EQ(v.size(), 0);
}

TEST(vector, pop_back_2) {
    Vector<C> v;
    v.push_back(0);
    v.pop_back();
    ASSERT_EQ(v.size(), 0);
}

TEST(vector, pop_back_3) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(*v.at(1).ptr, 1);
}

TEST(vector, insert_1) {
    Vector<C> v;
    v.insert(0, 0);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(*v.at(0).ptr, 0);
}

TEST(vector, insert_2) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(3);
    v.insert(2, 2);
    ASSERT_EQ(v.size(), 4);
    for (int i = 0; i < v.size(); ++i) {;
        ASSERT_EQ(*v.at(i).ptr, i);
    }
}

TEST(vector, insert_3) {
    Vector<C> v;
    v.push_back(0);
    v.push_back(1);
    v.insert(2, 2);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(*v.at(2).ptr, 2);
}

TEST(vector, resize_1) {
    // 0 -> 5
    // [] -> 0 0 0 0 0

    Vector<C> v;
    auto size = 5;
    v.resize(size, C(0));
    ASSERT_EQ(v.size(), size);
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(*v.at(0).ptr, 0);
    }
}

TEST(vector, resize_2) {
    Vector<C> v;
    auto size = 5;
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }
    v.resize(size, C(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).ptr, size - 1);
}

TEST(vector, resize_3) {
    // 3 -> 100
    // 0 1 2 -> 0 1 2 0 0 ... 0
    Vector<C> v;
    for (int i = 0; i < 3; ++i) {
        v.push_back(i);
    }
    size_t size = 100;
    v.resize(size, C(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).ptr, 0);
}

TEST(vector, resize_4) {
    // 100 -> 5
    // 0 1 2 ... 99 -> 0 1 2
    Vector<C> v;
    auto size = 3;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.resize(size, C(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).ptr, size - 1);
}

TEST(vector, clear) {
    Vector<C> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.clear();
    ASSERT_EQ(v.size(), 0);
}
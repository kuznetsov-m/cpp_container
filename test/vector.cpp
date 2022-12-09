#include <gtest/gtest.h>

#include "vector.h"
#include "test_object.h"

TEST(vector, constructor) {
    Vector<D> v;
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
}

TEST(vector, size) {
    Vector<D> v;
    for (size_t i = 0; i < 4; ++i) {
        v.push_back(i);
        ASSERT_EQ(v.size(), i + 1);
    }
}

TEST(vector, capacity) {
    Vector<D> v;
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
    Vector<D> v;
    D value(0);
    v.push_back(value);
    ASSERT_EQ(*v[0].m_value, *value.m_value);
}

TEST(vector, at) {
    Vector<D> v;
    D value(0);
    v.push_back(value);
    ASSERT_EQ(*v.at(0).m_value, *value.m_value);
}

TEST(vector, at_out_of_range) {
    Vector<D> v;
    try {
        v.at(0);
    }
    catch (const std::out_of_range& e) {
        ASSERT_EQ(strcmp(e.what(), "out_of_range"), 0);
    }
}

TEST(vector, push_back) {
    Vector<D> v;
    D value(0);
    for (int i = 0; i < v.size(); ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < v.size(); ++i) {
        ASSERT_EQ(*v.at(0).m_value, i);
    }
}

TEST(vector, front) {
    Vector<D> v;
    D value(0);
    v.push_back(value);
    v.push_back(1);
    ASSERT_EQ(*v.front().m_value, *value.m_value);
}

TEST(vector, back) {
    Vector<D> v;
    D value(1);
    v.push_back(0);
    v.push_back(value);
    ASSERT_EQ(*v.back().m_value, *(value.m_value));
}

TEST(vector, erase_1) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(0);
    ASSERT_EQ(*v.at(0).m_value, 1);
    ASSERT_EQ(*v.at(1).m_value, 2);
}

TEST(vector, erase_2) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(1);
    ASSERT_EQ(*v.at(0).m_value, 0);
    ASSERT_EQ(*v.at(1).m_value, 2);
}

TEST(vector, erase_3) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(2);
    ASSERT_EQ(*v.at(0).m_value, 0);
    ASSERT_EQ(*v.at(1).m_value, 1);
}

TEST(vector, erase_4) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(3);
    ASSERT_EQ(*v.at(0).m_value, 0);
    ASSERT_EQ(*v.at(1).m_value, 1);
    ASSERT_EQ(*v.at(2).m_value, 2);
}

TEST(vector, pop_back_1) {
    Vector<D> v;
    v.pop_back();
    ASSERT_EQ(v.size(), 0);
}

TEST(vector, pop_back_2) {
    Vector<D> v;
    v.push_back(0);
    v.pop_back();
    ASSERT_EQ(v.size(), 0);
}

TEST(vector, pop_back_3) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(*v.at(1).m_value, 1);
}

TEST(vector, insert_1) {
    Vector<D> v;
    v.insert(0, 0);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(*v.at(0).m_value, 0);
}

TEST(vector, insert_2) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(3);
    v.insert(2, 2);
    ASSERT_EQ(v.size(), 4);
    for (int i = 0; i < v.size(); ++i) {;
        ASSERT_EQ(*v.at(i).m_value, i);
    }
}

TEST(vector, insert_3) {
    Vector<D> v;
    v.push_back(0);
    v.push_back(1);
    v.insert(2, 2);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(*v.at(2).m_value, 2);
}

TEST(vector, resize_1) {
    // 0 -> 5
    // [] -> 0 0 0 0 0

    Vector<D> v;
    auto size = 5;
    v.resize(size, D(0));
    ASSERT_EQ(v.size(), size);
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(*v.at(0).m_value, 0);
    }
}

TEST(vector, resize_2) {
    Vector<D> v;
    auto size = 5;
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }
    v.resize(size, D(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).m_value, size - 1);
}

TEST(vector, resize_3) {
    // 3 -> 100
    // 0 1 2 -> 0 1 2 0 0 ... 0
    Vector<D> v;
    for (int i = 0; i < 3; ++i) {
        v.push_back(i);
    }
    size_t size = 100;
    v.resize(size, D(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).m_value, 0);
}

TEST(vector, resize_4) {
    // 100 -> 5
    // 0 1 2 ... 99 -> 0 1 2
    Vector<D> v;
    auto size = 3;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.resize(size, D(0));
    ASSERT_EQ(v.size(), size);
    ASSERT_EQ(*v.at(size - 1).m_value, size - 1);
}

TEST(vector, clear) {
    Vector<D> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.clear();
    ASSERT_EQ(v.size(), 0);
}
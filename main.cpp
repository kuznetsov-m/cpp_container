#include "vector.cpp"
#include "vector_2.h"

void run_tests() {
    {
        Vector<int> v;
        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }
    // size() capacity()
    {
        Vector<int> v;
        v.push_back(0);
        assert(v.size() == 1);
        assert(v.capacity() == 1);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        assert(v.size() == 2);
        assert(v.capacity() == 2);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        assert(v.size() == 3);
        assert(v.capacity() == 4);
    }
    // operator[]
    {
        Vector<int> v;
        auto value = 0;
        v.push_back(value);
        assert(v[0] == value);
    }
    // push_back() at()
    {
        Vector<int> v;
        for (int i = 0; i < v.size(); ++i) {
            v.push_back(i);
        }
        for (int i = 0; i < v.size(); ++i) {
            assert(v.at(i) == i);
        }
    }
    {
        Vector<int> v;
        try {
            v.at(0);
        }
        catch (const std::out_of_range& e) {
            assert(strcmp(e.what(), "out_of_range") == 0);
        }
    }
    // front()
    {
        Vector<int> v;
        int value = 0;
        v.push_back(value);
        v.push_back(1);
        assert(v.front() == value);
    }
    // back()
    {
        Vector<int> v;
        int value = 1;
        v.push_back(0);
        v.push_back(value);
        assert(v.back() == value);
    }
    // erase()
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(0);
        assert(v.at(0) == 1);
        assert(v.at(1) == 2);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(1);
        assert(v.at(0) == 0);
        assert(v.at(1) == 2);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(2);
        assert(v.at(0) == 0);
        assert(v.at(1) == 1);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(3);
        assert(v.at(0) == 0);
        assert(v.at(1) == 1);
        assert(v.at(2) == 2);
    }
    // pop_back()
    {
        Vector<int> v;
        v.pop_back();
        assert(v.size() == 0);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.pop_back();
        assert(v.size() == 0);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.pop_back();
        assert(v.size() == 2);
        assert(v.at(1) == 1);
    }
    // insert()
    {
        Vector<int> v;
        v.insert(0, 0);
        assert(v.size() == 1);
        assert(v.at(0) == 0);
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(3);
        v.insert(2, 2);
        assert(v.size() == 4);
        for (int i = 0; i < v.size(); ++i) {
            assert(v.at(i) == i);
        }
    }
    {
        Vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.insert(2, 2);
        assert(v.size() == 3);
        assert(v.at(2) == 2);
    }
    // resize()
    {
        // 0 -> 5
        // [] -> 0 0 0 0 0
        Vector<int> v;
        auto size = 5;
        v.resize(size);
        assert(v.size() == size);
        for (size_t i = 0; i < v.size(); ++i) {
            assert(v.at(0) == 0);
        }
    }
    {
        Vector<int> v;
        auto size = 5;
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
        v.resize(size);
        assert(v.size() == size);
        assert(v.at(size - 1) == size - 1);
    }
    {
        // 3 -> 100
        // 0 1 2 -> 0 1 2 0 0 ... 0
        Vector<int> v;
        for (int i = 0; i < 3; ++i) {
            v.push_back(i);
        }
        size_t size = 100;
        v.resize(size);
        assert(v.size() == size);
        assert(v.at(size - 1) == 0);
    }
    {
        // 100 -> 5
        // 0 1 2 ... 99 -> 0 1 2
        Vector<int> v;
        auto size = 3;
        for (int i = 0; i < 100; ++i) {
            v.push_back(i);
        }
        v.resize(size);
        assert(v.size() == size);
        assert(v.at(size - 1) == size - 1);
    }
}

#include "test_object.cpp"

void run_tests_2() {
    {
        Vector<C> v;
        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }
    // size() capacity()
    {
        Vector<C> v;
        v.push_back(0);
        assert(*v.at(0).ptr == 0);
        assert(v.size() == 1);
        assert(v.capacity() == 1);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        assert(v.size() == 2);
        assert(v.capacity() == 2);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        assert(v.size() == 3);
        assert(v.capacity() == 4);
    }
    // operator[]
    {
        Vector<C> v;
        C value(0);
        v.push_back(value);
        assert(*v[0].ptr == *value.ptr);
    }
    // push_back() at()
    {
        Vector<C> v;
        for (int i = 0; i < v.size(); ++i) {
            v.push_back(i);
        }
        for (int i = 0; i < v.size(); ++i) {
            assert(*v.at(i).ptr == i);
        }
    }
    {
        Vector<C> v;
        try {
            v.at(0);
        }
        catch (const std::out_of_range& e) {
            assert(strcmp(e.what(), "out_of_range") == 0);
        }
    }
    // front()
    {
        Vector<C> v;
        C value(0);
        v.push_back(value);
        v.push_back(1);
        assert(*v.front().ptr == *value.ptr);
    }
    // back()
    {
        Vector<C> v;
        C value(1);
        v.push_back(0);
        v.push_back(value);
        assert(*v.back().ptr == *(value.ptr));
    }
    // erase()
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(0);
        assert(*v.at(0).ptr == 1);
        assert(*v.at(1).ptr == 2);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(1);
        assert(*v.at(0).ptr == 0);
        assert(*v.at(1).ptr == 2);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(2);
        assert(*v.at(0).ptr == 0);
        assert(*v.at(1).ptr == 1);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.erase(3);
        assert(*v.at(0).ptr == 0);
        assert(*v.at(1).ptr == 1);
        assert(*v.at(2).ptr == 2);
    }
    // pop_back()
    {
        Vector<C> v;
        v.pop_back();
        assert(v.size() == 0);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.pop_back();
        assert(v.size() == 0);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.pop_back();
        assert(v.size() == 2);
        assert(*v.at(1).ptr == 1);
    }
    // insert()
    {
        Vector<C> v;
        v.insert(0, 0);
        assert(v.size() == 1);
        assert(*v.at(0).ptr == 0);
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(3);
        v.insert(2, 2);
        assert(v.size() == 4);
        for (int i = 0; i < v.size(); ++i) {
            assert(*v.at(i).ptr == i);
        }
    }
    {
        Vector<C> v;
        v.push_back(0);
        v.push_back(1);
        v.insert(2, 2);
        assert(v.size() == 3);
        assert(*v.at(2).ptr == 2);
    }
    // resize()
    {
        // 0 -> 5
        // [] -> 0 0 0 0 0
        Vector<C> v;
        auto size = 5;
        v.resize(size, C(0));
        assert(v.size() == size);
        for (size_t i = 0; i < v.size(); ++i) {
            assert(*v.at(0).ptr == 0);
        }
    }
    {
        Vector<C> v;
        auto size = 5;
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
        v.resize(size, C(0));
        assert(v.size() == size);
        assert(*v.at(size - 1).ptr == size - 1);
    }
    {
        // 3 -> 100
        // 0 1 2 -> 0 1 2 0 0 ... 0
        Vector<C> v;
        for (int i = 0; i < 3; ++i) {
            v.push_back(i);
        }
        size_t size = 100;
        v.resize(size, C(0));
        assert(v.size() == size);
        assert(*v.at(size - 1).ptr == 0);
    }
    {
        // 100 -> 5
        // 0 1 2 ... 99 -> 0 1 2
        Vector<C> v;
        auto size = 3;
        for (int i = 0; i < 100; ++i) {
            v.push_back(i);
        }
        v.resize(size, C(0));
        assert(v.size() == size);
        assert(*v.at(size - 1).ptr == size - 1);
    }
}

int main() {
    run_tests();
    run_tests_2();

   return 0;
}
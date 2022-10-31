#include <vector>
#include <iostream>

template<typename T>
class Vector {
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_arr = nullptr;

public:
    ~Vector() {
        m_size = 0;
        m_capacity = 0;
        delete[] m_arr;
    }

    size_t size() const noexcept {return m_size;}
    size_t capacity() const noexcept {return m_capacity;}
    void clear() noexcept {m_size = 0;}
    bool empty() const noexcept {return m_size == 0;}

    void resize(size_t new_size, const T& value = T()) {
        if (new_size > m_capacity) {
            reserve(new_size);
        }
        for (auto i = m_size; i < new_size; ++i) {
            m_arr[i] = value;
        }
        m_size = new_size;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {return;}
        
        auto new_arr = reinterpret_cast<T*>(new int8_t[new_capacity * sizeof(T)]);
        size_t i = 0;
        try {
            for (; i < m_size; ++i) {
                new(new_arr + i) T(m_arr[i]); // placement new
                // copy constructor exception safety
            }
        }
        catch (...) {
            for (auto j = i; j < i; ++j) {
                (new_arr + j)->~T();
            }
            delete[] reinterpret_cast<int8_t*>(new_arr);
            throw;
        }

        for (size_t i = 0; i < m_size; ++i) {
            T& item = m_arr[i];
            item.~T();
        }

        delete[] reinterpret_cast<int8_t*>(m_arr);
        m_arr = new_arr;
        m_capacity = new_capacity;
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            reserve(std::max(static_cast<size_t>(1), m_capacity * 2));
        }
        m_arr[m_size] = value;
        ++m_size;
    }

    void pop_back() {
        if (empty()) {return;} // std::vector UB
        --m_size;
        (m_arr + m_size)->~T();
    }

    void insert(const int index, const T& value) {
        if (index >= m_size) {
            reserve(index + 1);
        }
        m_arr[index] = value;
        ++m_size;
    }

    void erase(const int index) {
        if (index >= m_size) {return;} // std::vector : UB
        for(int i = index + 1; i < m_size; ++i) {
            m_arr[i - 1] = m_arr[i];
        }
        ++m_size;
    }

    T& operator[](size_t index) {
        return m_arr[index];
    }
    T& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("out_of_range");
        }
        return operator[](index);
    }

    T front() const noexcept {return m_arr[0];}
    T back() const noexcept {return m_arr[m_size - 1];}
};
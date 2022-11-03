#pragma once

#include <vector> // size_t

template<typename T>
class Vector {
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_arr = nullptr;
public:
    ~Vector();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;

    void reserve(size_t new_capacity);
    void resize(size_t new_size, const T& value = T());

    void push_back(const T& value);
    void pop_back();
};

template<typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < m_size; ++i) {
        T& item = m_arr[i];
        item.~T();
    }
    delete[] reinterpret_cast<int8_t*>(m_arr);
    m_size = 0;
    m_capacity = 0;
}

template<typename T>
size_t Vector<T>::size() const noexcept { return m_size; }

template<typename T>
size_t Vector<T>::capacity() const noexcept { return m_capacity; }

template<typename T>
void Vector<T>::clear() noexcept {
    // FIXME:
    m_size = 0;
}

template<typename T>
bool Vector<T>::empty() const noexcept { return m_size == 0; }

template<typename T>
void Vector<T>::reserve(size_t new_capacity) {
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

template<typename T>
void Vector<T>::resize(size_t new_size, const T& value) {
    if (new_size > m_capacity) {
        reserve(new_size);
    }
    for (auto i = m_size; i < new_size; ++i) {
        m_arr[i] = value;
    }
    m_size = new_size;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_arr[m_size] = value;
    ++m_size;
}

template<typename T>
void Vector<T>::pop_back() {
    if (empty()) {return;} // std::vector UB
    (m_arr + m_size - 1)->~T();
    --m_size;
}

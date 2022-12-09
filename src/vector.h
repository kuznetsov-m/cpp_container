#pragma once

#include <vector>    // size_t
#include <cstdint>   // int8_t
#include <stdexcept> // std::out_of_range

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
    void push_back(T&& value);
    void pop_back();
    void insert(size_t index, const T& value);
    void erase(size_t index);

    T& operator[](size_t index);
    T& at(size_t index);

    T front();
    T back();
};

template<typename T>
Vector<T>::~Vector() {
    clear();
    m_capacity = 0;
}

template<typename T>
size_t Vector<T>::size() const noexcept { return m_size; }

template<typename T>
size_t Vector<T>::capacity() const noexcept { return m_capacity; }

template<typename T>
void Vector<T>::clear() noexcept {
    if (m_size == 0) {
        return;
    }

    for (size_t i = 0; i < m_size; ++i) {
        T& item = m_arr[i];
        item.~T();
    }
    delete[] reinterpret_cast<int8_t*>(m_arr);
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

    new (m_arr + m_size) T(value);
    ++m_size;
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }

    new (m_arr + m_size) T(std::move(value));
    ++m_size;
}

template<typename T>
void Vector<T>::pop_back() {
    if (empty()) {return;} // std::vector UB
    (m_arr + m_size - 1)->~T();
    --m_size;
}

template<typename T>
void Vector<T>::insert(size_t index, const T& value) {
    if (index >= m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    if (index < m_size) {
        for (size_t i = m_size; i > index; --i) {
            m_arr[i] = m_arr[i - 1];
        }
    }
    m_arr[index] = value;
    ++m_size;
}

template<typename T>
void Vector<T>::erase(size_t index) {
    if (index >= m_size) {return;} // std::vector : UB
    for(int i = index + 1; i < m_size; ++i) {
        m_arr[i - 1] = m_arr[i];
    }
    m_arr[m_size - 1].~T();
    --m_size;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return m_arr[index];
}

template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("out_of_range");
    }
    return operator[](index);
}

template<typename T>
T Vector<T>::front() { return at(0); }

template<typename T>
T Vector<T>::back() { return at(m_size - 1); }
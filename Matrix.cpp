#include "Matrix.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace miit::algebra
{
    template<typename T>
    Matrix<T>::Matrix() : data(nullptr), size(0) {}

    template<typename T>
    Matrix<T>::Matrix(size_t size) : size(size)
    {
        if (size > 0) {
            data = std::make_unique<T[]>(size);
        }
        else {
            data = nullptr;
        }
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix& other) : size(other.size)
    {
        if (size > 0) {
            data = std::make_unique<T[]>(size);
            std::copy(other.data.get(), other.data.get() + size, data.get());
        }
        else {
            data = nullptr;
        }
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept : data(std::move(other.data)), size(other.size)
    {
        other.size = 0;
    }

    template<typename T>
    Matrix<T>::~Matrix() = default;

    // Операторы присваивания
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            size = other.size;
            if (size > 0) {
                data = std::make_unique<T[]>(size);
                std::copy(other.data.get(), other.data.get() + size, data.get());
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    // Операторы доступа
    template<typename T>
    T& Matrix<T>::operator[](size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Индекс за пределами диапазона");
        }
        return data[index];
    }

    template<typename T>
    const T& Matrix<T>::operator[](size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Индекс за пределами диапазона");
        }
        return data[index];
    }

    // Операторы сдвига (требуются по заданию)
    template<typename T>
    Matrix<T> Matrix<T>::operator<<(int shift) const
    {
        Matrix result(size);
        if (size > 0) {
            shift = shift % static_cast<int>(size);
            if (shift < 0) shift += static_cast<int>(size);

            for (size_t i = 0; i < size; ++i)
            {
                result.data[(i + shift) % size] = data[i];
            }
        }
        return result;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator>>(int shift) const
    {
        return *this << (-shift);
    }

    // Методы доступа
    template<typename T>
    size_t Matrix<T>::size() const
    {
        return size;
    }

    template<typename T>
    std::string Matrix<T>::to_string() const
    {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < size; ++i)
        {
            oss << data[i];
            if (i < size - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    template<typename T>
    void Matrix<T>::fill(Generator& generator)
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = static_cast<T>(generator.generate());
        }
    }

    template class Matrix<int>;
    template class Matrix<double>;

}
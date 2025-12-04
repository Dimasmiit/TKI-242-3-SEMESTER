#include <sstream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

class Generator;

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс для работы с одномерными массивами
     * @param T Тип элементов массива
     */
    template<typename T>
    class Matrix
    {
    private:
        std::unique_ptr<T[]> data;
        size_t size_;

    public:
        Matrix();
        explicit Matrix(const size_t size);
        Matrix(const T* values, const size_t size);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;
        explicit Matrix(const std::initializer_list<T> list);
        ~Matrix() = default;

        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;

        T& operator[](const size_t index);
        const T& operator[](const size_t index) const;

        Matrix operator<<(const int shift) const;
        Matrix operator>>(const int shift) const;

        size_t size() const;
        std::string to_string() const;
        void fill(const Generator& generator);
    };


    template<typename T>
    Matrix<T>::Matrix() : data(nullptr), size_(0) {}

    template<typename T>
    Matrix<T>::Matrix(size_t size) : size_(size)
    {
        if (size_ > 0) {
            data = std::make_unique<T[]>(size_);
        }
    }

    template<typename T>
    Matrix<T>::Matrix(const T* values, size_t size)
        : size_(size), data(std::make_unique<T[]>(size))
    {
        if (size == 0) {
            throw std::invalid_argument("Размер матрицы должен быть больше 0");
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] = values[i];
        }
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix& other)
        : size_(other.size_), data(std::make_unique<T[]>(other.size_))
    {
        std::copy(other.data.get(), other.data.get() + size_, data.get());
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept
        : data(std::move(other.data)), size_(other.size_)
    {
        other.size_ = 0;
    }

    template<typename T>
    Matrix<T>::Matrix(std::initializer_list<T> list)
        : size_(list.size()), data(std::make_unique<T[]>(list.size()))
    {
        std::copy(list.begin(), list.end(), data.get());
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            size_ = other.size_;
            if (size_ > 0) {
                data = std::make_unique<T[]>(size_);
                std::copy(other.data.get(), other.data.get() + size_, data.get());
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
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    template<typename T>
    T& Matrix<T>::operator[](size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Индекс за пределами диапазона");
        }
        return data[index];
    }

    template<typename T>
    const T& Matrix<T>::operator[](size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Индекс за пределами диапазона");
        }
        return data[index];
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator<<(int shift) const
    {
        Matrix result(size_);
        if (size_ > 0) {
            shift = shift % static_cast<int>(size_);
            if (shift < 0) shift += static_cast<int>(size_);

            for (size_t i = 0; i < size_; ++i)
            {
                result.data[(i + shift) % size_] = data[i];
            }
        }
        return result;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator>>(int shift) const
    {
        return *this << (-shift);
    }

    template<typename T>
    size_t Matrix<T>::size() const
    {
        return size_;
    }

    template<typename T>
    std::string Matrix<T>::to_string() const
    {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < size_; ++i)
        {
            oss << data[i];
            if (i < size_ - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    template<typename T>
    void Matrix<T>::fill(Generator& generator)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data[i] = static_cast<T>(generator.generate());
        }
    }
    template class Matrix<int>;
    template class Matrix<double>;
}
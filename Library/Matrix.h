#pragma once

#include "Generator.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

namespace miit::algebra {
    /**
    @brief Класс динамического массива шаблон 
    @tparam T тип элемента массива
    */
    template<typename T>
    class Matrix {
    private:
        std::unique_ptr<T[]> data;
        size_t size_;

    public:
        /**
        @brief конструктор по умолчанию
        */
        Matrix();

        /**
        @brief Конструктор с параметрами размера 
        */
        explicit Matrix(const size_t n);

        /**
        @brief Копирующий конструктор 
        */
        Matrix(const Matrix& other);

        /**
        @brief Переносящий конструктор 
        */
        Matrix(Matrix&& other) noexcept; 

        /**
        @brief Деструктор
        */
        ~Matrix() = default;

        /**
         * @brief Копирующее присваивание
         * @param other Массив для копирования
         * @return указатель на текущий объект
         */
        Matrix& operator=(const Matrix& other);

         /**
         * @brief Перемещающее присваивание
         * @param other Временный массив
         * @return указатель на текущий объект
         */
        Matrix& operator=(Matrix&& other) noexcept;

        /**
         * @brief Доступ к элементу массива по индексу (для изменения)
         * @param index Индекс элемента
         * @return Ссылка на элемент
         */
        T& operator[](const size_t index);

         /**
         * @brief Доступ к элементу массива по индексу (только чтение)
         * @param index Индекс элемента
         * @return Константная ссылка на элемент
         */
        const T& operator[](const size_t index) const;

        /**
         * @brief Возвращает размер массива
         * @return Количество элементов
         */
        size_t getSize() const;

        /**
         * @brief Проверяет, пустой ли массив?
         * @return true если массив пустой
         */
        bool isEmpty() const;

        /**
         * @brief Заполняет массив значениями из генератора 
         * @param gen Генератор значений
         */
        void fill(Generator& gen);

        /**
         * @brief Преобразует массив в строку
         * @return Строковое представление массива
         */
        std::string toString() const;

         /**
         * @brief получить доступ к первому элементу массива
         * @return указатель на первый элемент
         */
        T* getData();

        /**
         * @brief получить доступ к данным только для чтения
         * @return константный указатель на первый элемент
         */
        const T* getData() const;
    };

    template<typename T>
    Matrix<T>::Matrix() 
        : data(nullptr), size_(0)
    {
    }

    template<typename T>
    Matrix<T>::Matrix(size_t n) 
        : data(nullptr), size_(n)
    {
        if (n == 0) {
            throw std::invalid_argument("Размер массива не может быть 0");
        }
        data = std::make_unique<T[]>(n);
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix& other) 
        : data(nullptr), size_(other.size_)
    {
        if (other.data != nullptr) {
            data = std::make_unique<T[]>(size_);
            for (size_t i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept : data(std::move(other.data)), size_(other.size_)
    {
        other.size_ = 0;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other) {
            size_ = other.size_;
            
            if (other.data != nullptr) {
                data = std::make_unique<T[]>(size_);
                for (size_t i = 0; i < size_; i++) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        if (this != &other) {
            data = std::move(other.data);
            size_ = other.size_;
            
            other.size_ = 0;
        }
        return *this;
    }

    template<typename T>
    T& Matrix<T>::operator[](size_t index)
    {
        if (index >= size_) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    template<typename T>
    const T& Matrix<T>::operator[](size_t index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    template<typename T>
    size_t Matrix<T>::getSize() const
    {
        return size_;
    }

    template<typename T>
    bool Matrix<T>::isEmpty() const
    {
        return size_ == 0;
    }

    template<typename T>
    void Matrix<T>::fill(Generator& gen)
    {
        for (size_t i = 0; i < size_; i++) {
            data[i] = static_cast<T>(gen.generate());
        }
    }

    template<typename T>
    std::string Matrix<T>::toString() const
    {
        if (isEmpty()) {
            return "[]";
        }
        
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < size_; i++) {
            oss << data[i];
            if (i < size_ - 1) {
                oss << ", ";
            }
        }
        oss << "]";
        return oss.str();
    }

    template<typename T>
    T* Matrix<T>::getData()
    {
        return data.get();
    }

    template<typename T>
    const T* Matrix<T>::getData() const
    {
        return data.get();
    }
}
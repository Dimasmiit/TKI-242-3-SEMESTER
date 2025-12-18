#pragma once

#include <string>

using namespace std;

/**
 * @brief Абстрактный базовый класс Person - человек.
 */
class Person
{
protected:
    string full_name; // ФИО

public:
    /**
     * @brief Конструктор базового класса Person.
     * @param full_name ФИО человека.
     */
    Person(const string& full_name);

    /**
     * @brief Виртуальный деструктор для удаления наследников.
     */
    virtual ~Person() = default;

    /**
     * @brief Виртуальный метод для получения роли человека.
     * @return Строка с ролью.
     */
    virtual string get_role() const = 0;

    /**
     * @brief Виртуальный метод для вывода информации о человеке.
     */
    virtual void display() const = 0;

    /**
     * @brief Получение ФИО человека.
     * @return ФИО человека.
     */
    string get_full_name() const;
};

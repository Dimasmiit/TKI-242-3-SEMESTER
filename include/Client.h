#pragma once

#include "../include/Person.h"
#include <vector>
#include <memory>

using namespace std;

class LegalCase;

/**
 * @brief Абстрактный базовый класс Client представляет клиента.
 */
class Client : public Person
{
protected:
    vector<weak_ptr<LegalCase>> cases; // Дела, по которым проходит клиент

public:
    /**
     * @brief Конструктор базового класса Client.
     * @param full_name ФИО клиента.
     */
    Client(const string& full_name);

    /**
     * @brief Виртуальный деструктор для корректного удаления наследников.
     */
    virtual ~Client() = default;

    /**
     * @brief Чисто виртуальный метод для получения типа клиента.
     * @return Строка с типом клиента.
     */
    virtual string get_client_type() const = 0;

    /**
     * @brief Добавляет дело к списку дел клиента.
     * @param legal_case Указатель на дело.
     */
    void add_case(const shared_ptr<LegalCase>& legal_case);

    /**
     * @brief Получает список дел клиента.
     * @return Вектор указателей на дела.
     */
    vector<shared_ptr<LegalCase>> get_cases() const;

    /**
     * @brief Возвращает роль человека.
     * @return Строка "Клиент".
     */
    string get_role() const override;
};

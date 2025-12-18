#pragma once

#include "../include/Person.h"
#include <vector>
#include <memory>

using namespace std;

/**
 * @brief Перечисление специализаций адвокатов.
 */
enum class Specialization
{
    Housing,      // Жилищные дела
    Family,       // Семейные дела
    Criminal,     // Уголовные дела
    Labor,        // Трудовые споры
    Property      // Имущественные споры
};

/**
 * @brief Преобразует специализацию в строку.
 * @param spec Специализация.
 * @return Строковое представление специализации.
 */
string specialization_to_string(const Specialization spec);

class LegalCase;

/**
 * @brief Абстрактный базовый класс Lawyer представляет адвоката.
 */
class Lawyer : public Person
{
protected:
    Specialization specialization;           // Специализация адвоката
    vector<weak_ptr<LegalCase>> cases;       // Дела, которые ведет адвокат

public:
    /**
     * @brief Конструктор базового класса Lawyer.
     * @param full_name ФИО адвоката.
     * @param specialization Специализация адвоката.
     */
    Lawyer(const string& full_name, const Specialization specialization);

    /**
     * @brief Виртуальный деструктор для корректного удаления наследников.
     */
    virtual ~Lawyer() = default;

    /**
     * @brief Виртуальный метод для получения категории адвоката.
     * @return Строка с категорией.
     */
    virtual string get_category() const = 0;

    /**
     * @brief Добавляет дело к списку дел адвоката.
     * @param legal_case Указатель на дело.
     */
    void add_case(const shared_ptr<LegalCase>& legal_case);

    /**
     * @brief Получает список дел адвоката.
     * @return Вектор указателей на дела.
     */
    vector<shared_ptr<LegalCase>> get_cases() const;

    /**
     * @brief Получает специализацию адвоката.
     * @return Специализация.
     */
    Specialization get_specialization() const;

    /**
     * @brief Проверяет, свободен ли адвокат (нет активных дел).
     * @return true если адвокат свободен, false иначе.
     */
    bool is_available() const;

    /**
     * @brief Возвращает роль человека.
     * @return Строка "Адвокат".
     */
    string get_role() const override;
};

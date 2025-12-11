#pragma once

#include <string>
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

/**
 * @brief Базовый класс LegalCase представляет дело в адвокатской конторе.
 */
class LegalCase
{
protected:
    const string case_number;       // Номер дела
    const string case_content;      // Содержание дела
    const string lawyer_name;       // ФИО адвоката
    const string client_name;       // ФИО клиента
    const Specialization specialization; // Специализация дела
    bool is_active;                 // Активно ли дело (занят ли адвокат)

public:
    /**
     * @brief Конструктор базового класса дела.
     * @param case_number Номер дела.
     * @param case_content Содержание дела.
     * @param lawyer_name ФИО адвоката.
     * @param client_name ФИО клиента.
     * @param specialization Специализация дела.
     * @param is_active Активно ли дело.
     */
    LegalCase(const string& case_number, const string& case_content,
              const string& lawyer_name, const string& client_name,
              const Specialization specialization, const bool is_active = true);

    /**
     * @brief Виртуальный деструктор для корректного удаления наследников.
     */
    virtual ~LegalCase() = default;

    /**
     * @brief Чисто виртуальный метод для вывода информации о деле.
     */
    virtual void display() const = 0;

    /**
     * @brief Чисто виртуальный метод получения типа услуги.
     * @return Строка с типом услуги.
     */
    virtual string get_service_type() const = 0;

    /**
     * @brief Чисто виртуальный метод получения цены услуги.
     * @return Цена услуги.
     */
    virtual double get_service_price() const = 0;

    /**
     * @brief Получает номер дела.
     * @return Номер дела.
     */
    string get_case_number() const;

    /**
     * @brief Получает содержание дела.
     * @return Содержание дела.
     */
    string get_case_content() const;

    /**
     * @brief Получает ФИО адвоката.
     * @return ФИО адвоката.
     */
    string get_lawyer_name() const;

    /**
     * @brief Получает ФИО клиента.
     * @return ФИО клиента.
     */
    string get_client_name() const;

    /**
     * @brief Получает специализацию дела.
     * @return Специализация.
     */
    Specialization get_specialization() const;

    /**
     * @brief Проверяет, активно ли дело.
     * @return true если дело активно, false иначе.
     */
    bool get_is_active() const;

    /**
     * @brief Устанавливает статус активности дела.
     * @param active Новый статус.
     */
    void set_is_active(const bool active);
};

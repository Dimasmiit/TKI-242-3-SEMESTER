#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Lawyer;
class Client;
enum class Specialization;

/**
 * @brief Базовый класс LegalCase представляет дело в адвокатской конторе.
 */
class LegalCase
{
protected:
    const string case_number;               // Номер дела
    const string case_content;              // Содержание дела
    shared_ptr<Lawyer> lawyer;              // Адвокат
    shared_ptr<Client> client;              // Клиент
    bool is_active;                         // Активно ли дело (занят ли адвокат)

public:
    /**
     * @brief Конструктор базового класса дела.
     * @param case_number Номер дела.
     * @param case_content Содержание дела.
     * @param lawyer Указатель на адвоката.
     * @param client Указатель на клиента.
     * @param is_active Активно ли дело.
     */
    LegalCase(const string& case_number, const string& case_content,
              const shared_ptr<Lawyer>& lawyer, const shared_ptr<Client>& client,
              const bool is_active = true);

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
     * @brief Получает указатель на адвоката.
     * @return Указатель на адвоката.
     */
    shared_ptr<Lawyer> get_lawyer() const;

    /**
     * @brief Получает ФИО адвоката.
     * @return ФИО адвоката.
     */
    string get_lawyer_name() const;

    /**
     * @brief Получает указатель на клиента.
     * @return Указатель на клиента.
     */
    shared_ptr<Client> get_client() const;

    /**
     * @brief Получает ФИО клиента.
     * @return ФИО клиента.
     */
    string get_client_name() const;

    /**
     * @brief Получает специализацию дела (по специализации адвоката).
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

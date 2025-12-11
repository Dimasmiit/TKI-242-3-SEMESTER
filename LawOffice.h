#pragma once

#include "LegalCase.h"
#include <vector>
#include <memory>
#include <string>
#include <map>

/**
 * @brief Класс LawOffice - адвокатская контора.
 */
class LawOffice
{
private:
    vector<shared_ptr<LegalCase>> cases;  // Все дела
    map<string, Specialization> lawyers;  // Адвокаты и их специализации

public:
    /**
     * @brief Добавляет дело в контору.
     * @param legal_case Указатель на дело.
     */
    void add_case(const shared_ptr<LegalCase> legal_case);

    /**
     * @brief Регистрирует адвоката в конторе.
     * @param lawyer_name ФИО адвоката.
     * @param spec Специализация адвоката.
     */
    void register_lawyer(const string& lawyer_name, const Specialization spec);

    /**
     * @brief Показывает список предоставляемых услуг и их цены.
     * @return Вектор пар (тип услуги, средняя цена).
     */
    vector<pair<string, double>> get_services_with_prices() const;

    /**
     * @brief Выдает список клиентов, обращавшихся за данной услугой.
     * @param service_type Тип услуги.
     * @return Вектор имен клиентов.
     */
    vector<string> get_clients_by_service(const string& service_type) const;

    /**
     * @brief Выдает список свободных адвокатов по выбранной специализации.
     * @param spec Специализация.
     * @return Вектор имен свободных адвокатов.
     */
    vector<string> get_available_lawyers(const Specialization spec) const;

    /**
     * @brief Выдает содержание дела по его номеру.
     * @param case_number Номер дела.
     * @return Указатель на дело или nullptr, если не найдено.
     */
    shared_ptr<LegalCase> find_by_case_number(const string& case_number) const;

    /**
     * @brief Находит дела по ФИО клиента.
     * @param client_name ФИО клиента.
     * @return Вектор дел клиента.
     */
    vector<shared_ptr<LegalCase>> find_by_client_name(const string& client_name) const;

    /**
     * @brief Находит дела по ФИО адвоката.
     * @param lawyer_name ФИО адвоката.
     * @return Вектор дел адвоката.
     */
    vector<shared_ptr<LegalCase>> find_by_lawyer_name(const string& lawyer_name) const;

    /**
     * @brief Находит дела по специализации.
     * @param spec Специализация.
     * @return Вектор дел указанной специализации.
     */
    vector<shared_ptr<LegalCase>> find_by_specialization(const Specialization spec) const;

    /**
     * @brief Находит дела по типу услуги.
     * @param service_type Тип услуги.
     * @return Вектор дел указанного типа.
     */
    vector<shared_ptr<LegalCase>> find_by_service_type(const string& service_type) const;

    /**
     * @brief Находит дела по содержанию (ключевому слову).
     * @param keyword Ключевое слово для поиска.
     * @return Вектор дел, содержащих ключевое слово.
     */
    vector<shared_ptr<LegalCase>> find_by_content(const string& keyword) const;

    /**
     * @brief Находит активные дела.
     * @return Вектор активных дел.
     */
    vector<shared_ptr<LegalCase>> find_active_cases() const;

    /**
     * @brief Возвращает все дела в конторе.
     * @return Константная ссылка на вектор всех дел.
     */
    const vector<shared_ptr<LegalCase>>& get_all_cases() const;

    /**
     * @brief Возвращает количество дел в конторе.
     * @return Количество дел.
     */
    size_t size() const;
};

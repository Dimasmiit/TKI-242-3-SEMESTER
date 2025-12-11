#pragma once

#include "LegalCase.h"

/**
 * @brief Класс CourtCase представляет дело о ведении в суде.
 */
class CourtCase : public LegalCase
{
private:
    const string court_name;        // Название суда
    const string hearing_date;      // Дата заседания
    const string case_stage;        // Стадия дела (подготовка, слушание, апелляция)
    const double base_price;        // Базовая цена услуги

public:
    /**
     * @brief Конструктор дела о ведении в суде.
     * @param case_number Номер дела.
     * @param case_content Содержание дела.
     * @param lawyer_name ФИО адвоката.
     * @param client_name ФИО клиента.
     * @param specialization Специализация дела.
     * @param court_name Название суда.
     * @param hearing_date Дата заседания.
     * @param case_stage Стадия дела.
     * @param base_price Базовая цена услуги.
     * @param is_active Активно ли дело.
     */
    CourtCase(const string& case_number, const string& case_content,
              const string& lawyer_name, const string& client_name,
              const Specialization specialization, const string& court_name,
              const string& hearing_date, const string& case_stage,
              const double base_price, const bool is_active = true);

    /**
     * @brief Выводит информацию о деле.
     */
    void display() const override;

    /**
     * @brief Возвращает тип услуги.
     * @return Строка "Ведение дела в суде".
     */
    string get_service_type() const override;

    /**
     * @brief Возвращает цену услуги.
     * @return Цена услуги.
     */
    double get_service_price() const override;

    /**
     * @brief Получает название суда.
     * @return Название суда.
     */
    string get_court_name() const;

    /**
     * @brief Получает дату заседания.
     * @return Дата заседания.
     */
    string get_hearing_date() const;

    /**
     * @brief Получает стадию дела.
     * @return Стадия дела.
     */
    string get_case_stage() const;
};

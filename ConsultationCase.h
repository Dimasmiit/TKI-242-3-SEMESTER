#pragma once

#include "LegalCase.h"

/**
 * @brief Класс ConsultationCase представляет дело о консультации.
 */
class ConsultationCase : public LegalCase
{
private:
    const string consultation_topic;  // Тема консультации
    const double duration_hours;      // Продолжительность в часах
    const bool is_online;             // Онлайн или очная консультация
    const double hourly_rate;         // Почасовая ставка

public:
    /**
     * @brief Конструктор дела о консультации.
     * @param case_number Номер дела.
     * @param case_content Содержание дела.
     * @param lawyer_name ФИО адвоката.
     * @param client_name ФИО клиента.
     * @param specialization Специализация дела.
     * @param consultation_topic Тема консультации.
     * @param duration_hours Продолжительность в часах.
     * @param is_online Онлайн консультация.
     * @param hourly_rate Почасовая ставка.
     * @param is_active Активно ли дело.
     */
    ConsultationCase(const string& case_number, const string& case_content,
                     const string& lawyer_name, const string& client_name,
                     const Specialization specialization, const string& consultation_topic,
                     const double duration_hours, const bool is_online, const double hourly_rate,
                     const bool is_active = true);

    /**
     * @brief Выводит информацию о консультации.
     */
    void display() const override;

    /**
     * @brief Возвращает тип услуги.
     * @return Строка "Консультация".
     */
    string get_service_type() const override;

    /**
     * @brief Возвращает цену услуги (почасовая ставка * часы).
     * @return Цена услуги.
     */
    double get_service_price() const override;

    /**
     * @brief Получает тему консультации.
     * @return Тема консультации.
     */
    string get_consultation_topic() const;

    /**
     * @brief Получает продолжительность консультации.
     * @return Продолжительность в часах.
     */
    double get_duration_hours() const;

    /**
     * @brief Проверяет, онлайн ли консультация.
     * @return true если онлайн, false если очная.
     */
    bool get_is_online() const;

    /**
     * @brief Получает почасовую ставку.
     * @return Почасовая ставка.
     */
    double get_hourly_rate() const;
};

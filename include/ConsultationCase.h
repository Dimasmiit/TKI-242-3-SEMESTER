#pragma once

#include "../include/LegalCase.h"

class LawOffice;

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
     * @param lawyer Указатель на адвоката.
     * @param client Указатель на клиента.
     * @param consultation_topic Тема консультации.
     * @param duration_hours Продолжительность в часах.
     * @param is_online Онлайн консультация.
     * @param hourly_rate Почасовая ставка.
     * @param is_active Активно ли дело.
     */
    ConsultationCase(const string& case_number, const string& case_content,
                     const shared_ptr<Lawyer>& lawyer, const shared_ptr<Client>& client,
                     const string& consultation_topic, const double duration_hours,
                     const bool is_online, const double hourly_rate,
                     const bool is_active = true);

    /**
     * @brief Фабричный метод для создания консультации с регистрацией в конторе.
     * @param case_number Номер дела.
     * @param case_content Содержание дела.
     * @param lawyer Указатель на адвоката.
     * @param client Указатель на клиента.
     * @param consultation_topic Тема консультации.
     * @param duration_hours Продолжительность в часах.
     * @param is_online Онлайн консультация.
     * @param hourly_rate Почасовая ставка.
     * @param office Ссылка на контору.
     * @param is_active Активно ли дело.
     * @return shared_ptr на созданное дело.
     */
    static shared_ptr<ConsultationCase> create(const string& case_number,
                                                const string& case_content,
                                                const shared_ptr<Lawyer>& lawyer,
                                                const shared_ptr<Client>& client,
                                                const string& consultation_topic,
                                                const double duration_hours,
                                                const bool is_online,
                                                const double hourly_rate,
                                                LawOffice& office,
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

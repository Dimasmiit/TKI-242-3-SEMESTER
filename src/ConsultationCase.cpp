#include "../include/ConsultationCase.h"
#include "../include/LawOffice.h"
#include "../include/Lawyer.h"
#include "../include/Client.h"
#include <iostream>

ConsultationCase::ConsultationCase(const string& case_number, const string& case_content,
                                   const shared_ptr<Lawyer>& lawyer, const shared_ptr<Client>& client,
                                   const string& consultation_topic, const double duration_hours,
                                   const bool is_online, const double hourly_rate,
                                   const bool is_active)
    : LegalCase(case_number, case_content, lawyer, client, is_active),
      consultation_topic(consultation_topic), duration_hours(duration_hours),
      is_online(is_online), hourly_rate(hourly_rate) {}

shared_ptr<ConsultationCase> ConsultationCase::create(const string& case_number,
                                                       const string& case_content,
                                                       const shared_ptr<Lawyer>& lawyer,
                                                       const shared_ptr<Client>& client,
                                                       const string& consultation_topic,
                                                       const double duration_hours,
                                                       const bool is_online,
                                                       const double hourly_rate,
                                                       LawOffice& office,
                                                       const bool is_active)
{
    auto consultation = make_shared<ConsultationCase>(case_number, case_content, lawyer, client,
                                                       consultation_topic, duration_hours,
                                                       is_online, hourly_rate, is_active);
    office.add_case(consultation);
    return consultation;
}

void ConsultationCase::display() const
{
    cout << "Дело: Консультация" << endl;
    cout << "Номер дела: " << case_number << endl;
    cout << "Клиент: " << (client ? client->get_full_name() : "Не назначен") << endl;
    cout << "Адвокат: " << (lawyer ? lawyer->get_full_name() : "Не назначен") << endl;
    cout << "Специализация: " << specialization_to_string(get_specialization()) << endl;
    cout << "Тема консультации: " << consultation_topic << endl;
    cout << "Продолжительность: " << duration_hours << " ч." << endl;
    cout << "Формат: " << (is_online ? "Онлайн" : "Очная") << endl;
    cout << "Почасовая ставка: " << hourly_rate << " руб./ч." << endl;
    cout << "Итоговая стоимость: " << get_service_price() << " руб." << endl;
    cout << "Статус: " << (is_active ? "Активно" : "Завершено") << endl;
    cout << "Содержание: " << case_content << endl;
    cout << endl;
}

string ConsultationCase::get_service_type() const
{
    return "Консультация";
}

double ConsultationCase::get_service_price() const
{
    return hourly_rate * duration_hours;
}

string ConsultationCase::get_consultation_topic() const
{
    return consultation_topic;
}

double ConsultationCase::get_duration_hours() const
{
    return duration_hours;
}

bool ConsultationCase::get_is_online() const
{
    return is_online;
}

double ConsultationCase::get_hourly_rate() const
{
    return hourly_rate;
}

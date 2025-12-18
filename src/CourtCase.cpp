#include "../include/CourtCase.h"
#include "../include/LawOffice.h"
#include "../include/Lawyer.h"
#include "../include/Client.h"
#include <iostream>

CourtCase::CourtCase(const string& case_number, const string& case_content,
                     const shared_ptr<Lawyer>& lawyer, const shared_ptr<Client>& client,
                     const string& court_name, const string& hearing_date,
                     const string& case_stage, const double base_price,
                     const bool is_active)
    : LegalCase(case_number, case_content, lawyer, client, is_active),
      court_name(court_name), hearing_date(hearing_date),
      case_stage(case_stage), base_price(base_price) {}

shared_ptr<CourtCase> CourtCase::create(const string& case_number,
                                        const string& case_content,
                                        const shared_ptr<Lawyer>& lawyer,
                                        const shared_ptr<Client>& client,
                                        const string& court_name,
                                        const string& hearing_date,
                                        const string& case_stage,
                                        const double base_price,
                                        LawOffice& office,
                                        const bool is_active)
{
    auto court_case = make_shared<CourtCase>(case_number, case_content, lawyer, client,
                                              court_name, hearing_date, case_stage,
                                              base_price, is_active);
    office.add_case(court_case);
    return court_case;
}

void CourtCase::display() const
{
    cout << "Дело: Ведение в суде" << endl;
    cout << "Номер дела: " << case_number << endl;
    cout << "Клиент: " << (client ? client->get_full_name() : "Не назначен") << endl;
    cout << "Адвокат: " << (lawyer ? lawyer->get_full_name() : "Не назначен") << endl;
    cout << "Специализация: " << specialization_to_string(get_specialization()) << endl;
    cout << "Суд: " << court_name << endl;
    cout << "Дата заседания: " << hearing_date << endl;
    cout << "Стадия дела: " << case_stage << endl;
    cout << "Стоимость услуги: " << base_price << " руб." << endl;
    cout << "Статус: " << (is_active ? "Активно" : "Завершено") << endl;
    cout << "Содержание: " << case_content << endl;
    cout << endl;
}

string CourtCase::get_service_type() const
{
    return "Ведение дела в суде";
}

double CourtCase::get_service_price() const
{
    return base_price;
}

string CourtCase::get_court_name() const
{
    return court_name;
}

string CourtCase::get_hearing_date() const
{
    return hearing_date;
}

string CourtCase::get_case_stage() const
{
    return case_stage;
}

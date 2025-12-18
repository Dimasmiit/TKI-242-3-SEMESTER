#include "../include/OfficeLawyer.h"
#include "../include/LawOffice.h"
#include <iostream>

OfficeLawyer::OfficeLawyer(const string& full_name, const Specialization specialization,
                           const string& category)
    : Lawyer(full_name, specialization), category(category) {}

shared_ptr<OfficeLawyer> OfficeLawyer::create(const string& full_name,
                                               const Specialization specialization,
                                               const string& category,
                                               LawOffice& office)
{
    auto lawyer = make_shared<OfficeLawyer>(full_name, specialization, category);
    office.add_lawyer(lawyer);
    return lawyer;
}

void OfficeLawyer::display() const
{
    cout << "Адвокат" << endl;
    cout << "ФИО: " << full_name << endl;
    cout << "Специализация: " << specialization_to_string(specialization) << endl;
    cout << "Категория: " << category << endl;
    cout << "Статус: " << (is_available() ? "Свободен" : "Занят") << endl;
    cout << endl;
}

string OfficeLawyer::get_category() const
{
    return category;
}

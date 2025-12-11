#include "LegalCase.h"

string specialization_to_string(const Specialization spec)
{
    switch (spec)
    {
        case Specialization::Housing:
            return "Жилищные дела";
        case Specialization::Family:
            return "Семейные дела";
        case Specialization::Criminal:
            return "Уголовные дела";
        case Specialization::Labor:
            return "Трудовые споры";
        case Specialization::Property:
            return "Имущественные споры";
        default:
            return "Неизвестно";
    }
}

LegalCase::LegalCase(const string& case_number, const string& case_content,
                     const string& lawyer_name, const string& client_name,
                     const Specialization specialization, const bool is_active)
    : case_number(case_number), case_content(case_content),
      lawyer_name(lawyer_name), client_name(client_name),
      specialization(specialization), is_active(is_active) {}

string LegalCase::get_case_number() const
{
    return case_number;
}

string LegalCase::get_case_content() const
{
    return case_content;
}

string LegalCase::get_lawyer_name() const
{
    return lawyer_name;
}

string LegalCase::get_client_name() const
{
    return client_name;
}

Specialization LegalCase::get_specialization() const
{
    return specialization;
}

bool LegalCase::get_is_active() const
{
    return is_active;
}

void LegalCase::set_is_active(const bool active)
{
    is_active = active;
}

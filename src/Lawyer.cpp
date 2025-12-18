#include "../include/Lawyer.h"
#include "../include/LegalCase.h"

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

Lawyer::Lawyer(const string& full_name, const Specialization specialization)
    : Person(full_name), specialization(specialization) {}

void Lawyer::add_case(const shared_ptr<LegalCase>& legal_case)
{
    cases.push_back(legal_case);
}

vector<shared_ptr<LegalCase>> Lawyer::get_cases() const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& weak_case : cases)
    {
        if (auto legal_case = weak_case.lock())
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

Specialization Lawyer::get_specialization() const
{
    return specialization;
}

bool Lawyer::is_available() const
{
    for (const auto& weak_case : cases)
    {
        if (auto legal_case = weak_case.lock())
        {
            if (legal_case->get_is_active())
            {
                return false;
            }
        }
    }
    return true;
}

string Lawyer::get_role() const
{
    return "Адвокат";
}

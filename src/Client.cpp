#include "../include/Client.h"
#include "../include/LegalCase.h"

Client::Client(const string& full_name)
    : Person(full_name) {}

void Client::add_case(const shared_ptr<LegalCase>& legal_case)
{
    cases.push_back(legal_case);
}

vector<shared_ptr<LegalCase>> Client::get_cases() const
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

string Client::get_role() const
{
    return "Клиент";
}

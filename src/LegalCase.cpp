#include "../include/LegalCase.h"
#include "../include/Lawyer.h"
#include "../include/Client.h"

LegalCase::LegalCase(const string& case_number, const string& case_content,
                     const shared_ptr<Lawyer>& lawyer, const shared_ptr<Client>& client,
                     const bool is_active)
    : case_number(case_number), case_content(case_content),
      lawyer(lawyer), client(client), is_active(is_active) {}

string LegalCase::get_case_number() const
{
    return case_number;
}

string LegalCase::get_case_content() const
{
    return case_content;
}

shared_ptr<Lawyer> LegalCase::get_lawyer() const
{
    return lawyer;
}

string LegalCase::get_lawyer_name() const
{
    if (lawyer)
    {
        return lawyer->get_full_name();
    }
    return "";
}

shared_ptr<Client> LegalCase::get_client() const
{
    return client;
}

string LegalCase::get_client_name() const
{
    if (client)
    {
        return client->get_full_name();
    }
    return "";
}

Specialization LegalCase::get_specialization() const
{
    if (lawyer)
    {
        return lawyer->get_specialization();
    }
    return Specialization::Housing; // По умолчанию
}

bool LegalCase::get_is_active() const
{
    return is_active;
}

void LegalCase::set_is_active(const bool active)
{
    is_active = active;
}

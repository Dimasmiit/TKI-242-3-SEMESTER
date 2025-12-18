#include "../include/LawOffice.h"
#include <algorithm>
#include <set>
#include <map>

void LawOffice::add_case(const shared_ptr<LegalCase>& legal_case)
{
    cases.push_back(legal_case);
}

void LawOffice::add_lawyer(const shared_ptr<Lawyer>& lawyer)
{
    lawyers.push_back(lawyer);
}

void LawOffice::add_client(const shared_ptr<Client>& client)
{
    clients.push_back(client);
}

vector<pair<string, double>> LawOffice::get_services_with_prices() const
{
    map<string, pair<double, int>> service_totals;

    for (const auto& legal_case : cases)
    {
        const string service_type = legal_case->get_service_type();
        const double price = legal_case->get_service_price();

        if (service_totals.find(service_type) == service_totals.end())
        {
            service_totals[service_type] = {price, 1};
        }
        else
        {
            service_totals[service_type].first += price;
            service_totals[service_type].second++;
        }
    }

    vector<pair<string, double>> result;
    for (const auto& entry : service_totals)
    {
        const double avg_price = entry.second.first / entry.second.second;
        result.push_back({entry.first, avg_price});
    }

    return result;
}

vector<string> LawOffice::get_clients_by_service(const string& service_type) const
{
    set<string> unique_clients;

    for (const auto& legal_case : cases)
    {
        if (legal_case->get_service_type() == service_type)
        {
            unique_clients.insert(legal_case->get_client_name());
        }
    }

    return vector<string>(unique_clients.begin(), unique_clients.end());
}

vector<string> LawOffice::get_available_lawyers(const Specialization spec) const
{
    vector<string> available;
    for (const auto& lawyer : lawyers)
    {
        if (lawyer->get_specialization() == spec && lawyer->is_available())
        {
            available.push_back(lawyer->get_full_name());
        }
    }

    return available;
}

shared_ptr<LegalCase> LawOffice::find_by_case_number(const string& case_number) const
{
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_case_number() == case_number)
        {
            return legal_case;
        }
    }
    return nullptr;
}

vector<shared_ptr<LegalCase>> LawOffice::find_by_client_name(const string& client_name) const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_client_name() == client_name)
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

vector<shared_ptr<LegalCase>> LawOffice::find_by_lawyer_name(const string& lawyer_name) const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_lawyer_name() == lawyer_name)
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

vector<shared_ptr<LegalCase>> LawOffice::find_by_specialization(const Specialization spec) const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_specialization() == spec)
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

vector<shared_ptr<LegalCase>> LawOffice::find_by_service_type(const string& service_type) const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_service_type() == service_type)
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

vector<shared_ptr<LegalCase>> LawOffice::find_by_content(const string& keyword) const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_case_content().find(keyword) != string::npos)
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

vector<shared_ptr<LegalCase>> LawOffice::find_active_cases() const
{
    vector<shared_ptr<LegalCase>> result;
    for (const auto& legal_case : cases)
    {
        if (legal_case->get_is_active())
        {
            result.push_back(legal_case);
        }
    }
    return result;
}

shared_ptr<Lawyer> LawOffice::find_lawyer_by_name(const string& name) const
{
    for (const auto& lawyer : lawyers)
    {
        if (lawyer->get_full_name() == name)
        {
            return lawyer;
        }
    }
    return nullptr;
}

shared_ptr<Client> LawOffice::find_client_by_name(const string& name) const
{
    for (const auto& client : clients)
    {
        if (client->get_full_name() == name)
        {
            return client;
        }
    }
    return nullptr;
}

const vector<shared_ptr<LegalCase>>& LawOffice::get_all_cases() const
{
    return cases;
}

const vector<shared_ptr<Lawyer>>& LawOffice::get_all_lawyers() const
{
    return lawyers;
}

const vector<shared_ptr<Client>>& LawOffice::get_all_clients() const
{
    return clients;
}

size_t LawOffice::size() const
{
    return cases.size();
}

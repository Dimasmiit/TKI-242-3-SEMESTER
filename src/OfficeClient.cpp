#include "../include/OfficeClient.h"
#include "../include/LawOffice.h"
#include <iostream>

OfficeClient::OfficeClient(const string& full_name, const string& phone_number)
    : Client(full_name), phone_number(phone_number) {}

shared_ptr<OfficeClient> OfficeClient::create(const string& full_name,
                                               const string& phone_number,
                                               LawOffice& office)
{
    auto client = make_shared<OfficeClient>(full_name, phone_number);
    office.add_client(client);
    return client;
}

void OfficeClient::display() const
{
    cout << "Клиент" << endl;
    cout << "ФИО: " << full_name << endl;
    cout << "Телефон: " << phone_number << endl;
    cout << "Количество дел: " << get_cases().size() << endl;
    cout << endl;
}

string OfficeClient::get_client_type() const
{
    return "Клиент конторы";
}

string OfficeClient::get_phone_number() const
{
    return phone_number;
}

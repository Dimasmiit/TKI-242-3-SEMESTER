#include "../include/LawOffice.h"
#include "../include/CourtCase.h"
#include "../include/ConsultationCase.h"
#include "../include/OfficeLawyer.h"
#include "../include/OfficeClient.h"
#include <iostream>
#include <memory>

int main(void)
{
    LawOffice office;

    // Регистрация адвокатов в конторе
    auto lawyer_altov = OfficeLawyer::create("Альтов Станислав Викторович", 
                                              Specialization::Housing, "Высшая", office);
    auto lawyer_borisova = OfficeLawyer::create("Борисова Виктория Евгеньевна", 
                                                 Specialization::Family, "Высшая", office);
    auto lawyer_voronin = OfficeLawyer::create("Воронин Константин Сергеевич", 
                                                Specialization::Criminal, "Первая", office);
    auto lawyer_gavrilenko = OfficeLawyer::create("Гавриленко Светлана Павловна", 
                                                   Specialization::Labor, "Первая", office);
    auto lawyer_danilov = OfficeLawyer::create("Данилов Игорь Валентинович", 
                                                Specialization::Property, "Высшая", office);
    auto lawyer_efimova = OfficeLawyer::create("Ефимова Наталья Александровна", 
                                                Specialization::Family, "Первая", office);

    // Регистрация клиентов
    auto client_lukin = OfficeClient::create("Лукин Виталий Геннадьевич", 
                                              "+7-999-111-22-33", office);
    auto client_maksimova = OfficeClient::create("Максимова Анастасия Олеговна", 
                                                  "+7-999-222-33-44", office);
    auto client_nikiforov = OfficeClient::create("Никифоров Евгений Александрович", 
                                                  "+7-999-333-44-55", office);
    auto client_orlova = OfficeClient::create("Орлова Елизавета Викторовна", 
                                               "+7-999-444-55-66", office);
    auto client_ryzhov = OfficeClient::create("Рыжов Сергей Михайлович", 
                                               "+7-999-555-66-77", office);
    auto client_sorokina = OfficeClient::create("Сорокина Татьяна Дмитриевна", 
                                                 "+7-999-666-77-88", office);
    auto client_tihonov = OfficeClient::create("Тихонов Павел Сергеевич", 
                                                "+7-999-777-88-99", office);

    // Создание дел о ведении в суде
    auto case1 = CourtCase::create(
        "ДЛ-2025-001", "Спор о праве собственности на квартиру",
        lawyer_altov, client_lukin,
        "Московский районный суд", "15.02.2025", "Подготовка к слушанию", 
        150000.0, office);
    lawyer_altov->add_case(case1);
    client_lukin->add_case(case1);

    auto case2 = CourtCase::create(
        "ДЛ-2025-002", "Бракоразводный процесс с разделом имущества",
        lawyer_borisova, client_maksimova,
        "Центральный районный суд", "20.02.2025", "Первое слушание", 
        120000.0, office);
    lawyer_borisova->add_case(case2);
    client_maksimova->add_case(case2);

    auto case3 = CourtCase::create(
        "ДЛ-2024-015", "Защита по уголовному делу о мошенничестве",
        lawyer_voronin, client_nikiforov,
        "Городской суд", "10.01.2025", "Апелляция", 
        250000.0, office);
    lawyer_voronin->add_case(case3);
    client_nikiforov->add_case(case3);

    auto case4 = CourtCase::create(
        "ДЛ-2025-003", "Трудовой спор о незаконном увольнении",
        lawyer_gavrilenko, client_orlova,
        "Арбитражный суд", "25.02.2025", "Подготовка документов", 
        80000.0, office);
    lawyer_gavrilenko->add_case(case4);
    client_orlova->add_case(case4);

    // Создание дел о консультациях
    auto case5 = ConsultationCase::create(
        "ДЛ-2025-004", "Консультация по вопросам наследства",
        lawyer_danilov, client_ryzhov,
        "Оформление наследства на недвижимость",
        2.0, false, 5000.0, office, false);
    lawyer_danilov->add_case(case5);
    client_ryzhov->add_case(case5);

    auto case6 = ConsultationCase::create(
        "ДЛ-2025-005", "Консультация по алиментам",
        lawyer_efimova, client_sorokina,
        "Порядок взыскания алиментов",
        1.5, true, 4000.0, office, false);
    lawyer_efimova->add_case(case6);
    client_sorokina->add_case(case6);

    auto case7 = ConsultationCase::create(
        "ДЛ-2025-006", "Консультация по жилищным вопросам",
        lawyer_altov, client_tihonov,
        "Приватизация жилья",
        1.0, true, 4500.0, office);
    lawyer_altov->add_case(case7);
    client_tihonov->add_case(case7);

    auto case8 = ConsultationCase::create(
        "ДЛ-2025-007", "Консультация по разводу",
        lawyer_borisova, client_maksimova,
        "Процедура развода через суд",
        2.0, false, 5000.0, office, false);
    lawyer_borisova->add_case(case8);
    client_maksimova->add_case(case8);

    // Демонстрация работы конторы
    cout << endl;
    cout << "Всего дел в конторе: " << office.size() << endl;
    cout << "Всего адвокатов: " << office.get_all_lawyers().size() << endl;
    cout << "Всего клиентов: " << office.get_all_clients().size() << endl;
    cout << endl;

    // Вывод всех дел
    for (const auto& legal_case : office.get_all_cases())
    {
        legal_case->display();
    }

    // Задание 1: Показать список предоставляемых услуг и их цену

    const auto services = office.get_services_with_prices();
    for (const auto& service : services)
    {
        cout << "Услуга: " << service.first << endl;
        cout << "Средняя цена: " << service.second << " руб." << endl;
        cout << endl;
    }

    // Задание 2: Выдать список клиентов, обращавшихся за данной услугой
    cout << "Клиенты, обращавшиеся за услугой 'Ведение дела в суде':" << endl;
    const auto court_clients = office.get_clients_by_service("Ведение дела в суде");
    for (const auto& client : court_clients)
    {
        cout << "- " << client << endl;
    }
    cout << endl;

    cout << "Клиенты, обращавшиеся за услугой 'Консультация':" << endl;
    const auto consultation_clients = office.get_clients_by_service("Консультация");
    for (const auto& client : consultation_clients)
    {
        cout << "- " << client << endl;
    }
    cout << endl;

    // Задание 3: Выдать список свободных адвокатов по выбранной услуге

    cout << "Свободные адвокаты по семейным делам:" << endl;
    const auto available_family = office.get_available_lawyers(Specialization::Family);
    if (available_family.empty())
    {
        cout << "Нет свободных адвокатов" << endl;
    }
    else
    {
        for (const auto& lawyer : available_family)
        {
            cout << "- " << lawyer << endl;
        }
    }
    cout << endl;

    cout << "Свободные адвокаты по имущественным спорам:" << endl;
    const auto available_property = office.get_available_lawyers(Specialization::Property);
    if (available_property.empty())
    {
        cout << "Нет свободных адвокатов" << endl;
    }
    else
    {
        for (const auto& lawyer : available_property)
        {
            cout << "- " << lawyer << endl;
        }
    }
    cout << endl;

    // Задание 4: Выдать содержание Дела по его номеру
    cout << "Поиск дела ДЛ-2025-002:" << endl;
    const auto found_case = office.find_by_case_number("ДЛ-2025-002");
    if (found_case)
    {
        found_case->display();
    }
    else
    {
        cout << "Дело не найдено" << endl;
    }

    cout << "Поиск дела ДЛ-777-999:" << endl;
    const auto not_found_case = office.find_by_case_number("ДЛ-777-999");
    if (not_found_case)
    {
        not_found_case->display();
    }
    else
    {
        cout << "Дело не найдено" << endl;
    }
    cout << endl;

    cout << "Дела клиента Максимова Анастасия Ивановна:" << endl;
    const auto client_cases = office.find_by_client_name("Максимова Анастасия Ивановна");
    for (const auto& legal_case : client_cases)
    {
        legal_case->display();
    }

    const auto active_cases = office.find_active_cases();
    cout << "Количество активных дел: " << active_cases.size() << endl;
    for (const auto& legal_case : active_cases)
    {
        cout << "- " << legal_case->get_case_number() << ": "
             << legal_case->get_client_name() << " (адвокат: "
             << legal_case->get_lawyer_name() << ")" << endl;
    }
    cout << endl;

    cout << "Семейные дела:" << endl;
    const auto family_cases = office.find_by_specialization(Specialization::Family);
    for (const auto& legal_case : family_cases)
    {
        legal_case->display();
    }

    return 0;
}

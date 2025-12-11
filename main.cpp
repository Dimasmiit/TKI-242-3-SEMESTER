#include "LawOffice.h"
#include "CourtCase.h"
#include "ConsultationCase.h"
#include <iostream>
#include <memory>

int main(void)
{
    LawOffice office;

    // Регистрация адвокатов в конторе
    office.register_lawyer("Альтов Станислав Викторович", Specialization::Housing);
    office.register_lawyer("Борисова Виктория Евгеньевна", Specialization::Family);
    office.register_lawyer("Воронин Константин Сергеевич", Specialization::Criminal);
    office.register_lawyer("Гавриленко Светлана Павловна", Specialization::Labor);
    office.register_lawyer("Данилов Игорь Валентинович", Specialization::Property);
    office.register_lawyer("Ефимова Наталья Александровна", Specialization::Family);

    // Создание дел о ведении в суде
    office.add_case(make_shared<CourtCase>(
        "ДЛ-2025-001", "Спор о праве собственности на квартиру",
        "Альтов Станислав Викторович", "Лукин Виталий Геннадьевич",
        Specialization::Housing, "Московский районный суд",
        "15.02.2025", "Подготовка к слушанию", 150000.0));

    office.add_case(make_shared<CourtCase>(
        "ДЛ-2025-002", "Бракоразводный процесс с разделом имущества",
        "Борисова Виктория Евгеньевна", "Максимова Анастасия Олеговна",
        Specialization::Family, "Центральный районный суд",
        "20.02.2025", "Первое слушание", 120000.0));

    office.add_case(make_shared<CourtCase>(
        "ДЛ-2024-015", "Защита по уголовному делу о мошенничестве",
        "Воронин Константин Сергеевич", "Никифоров Евгений Александрович",
        Specialization::Criminal, "Городской суд",
        "10.01.2025", "Апелляция", 250000.0));

    office.add_case(make_shared<CourtCase>(
        "ДЛ-2025-003", "Трудовой спор о незаконном увольнении",
        "Гавриленко Светлана Павловна", "Орлова Елизавета Викторовна",
        Specialization::Labor, "Арбитражный суд",
        "25.02.2025", "Подготовка документов", 80000.0));

    // Создание дел о консультациях
    office.add_case(make_shared<ConsultationCase>(
        "ДЛ-2025-004", "Консультация по вопросам наследства",
        "Данилов Игорь Валентинович", "Рыжов Сергей Михайлович",
        Specialization::Property, "Оформление наследства на недвижимость",
        2.0, false, 5000.0, false));

    office.add_case(make_shared<ConsultationCase>(
        "ДЛ-2025-005", "Консультация по алиментам",
        "Ефимова Наталья Александровна", "Сорокина Татьяна Дмитриевна",
        Specialization::Family, "Порядок взыскания алиментов",
        1.5, true, 4000.0, false));

    office.add_case(make_shared<ConsultationCase>(
        "ДЛ-2025-006", "Консультация по жилищным вопросам",
        "Альтов Станислав Викторович", "Тихонов Павел Сергеевич",
        Specialization::Housing, "Приватизация жилья",
        1.0, true, 4500.0));

    office.add_case(make_shared<ConsultationCase>(
        "ДЛ-2025-007", "Консультация по разводу",
        "Борисова Виктория Евгеньевна", "Максимова Анастасия Олеговна",
        Specialization::Family, "Процедура развода через суд",
        2.0, false, 5000.0, false));

    // Демонстрация работы конторы
    cout << "Всего дел в конторе: " << office.size() << endl << endl;

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
    const auto court_clients = office.get_clients_by_service("Ведение дела в суде");
    for (const auto& client : court_clients)
    {
        cout << "- " << client << endl;
    }
    cout << endl;

    const auto consultation_clients = office.get_clients_by_service("Консультация");
    for (const auto& client : consultation_clients)
    {
        cout << "- " << client << endl;
    }
    cout << endl;

    // Задание 3: Выдать список свободных адвокатов по выбранной услуге
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
    const auto found_case = office.find_by_case_number("ДЛ-2025-002");
    if (found_case)
    {
        found_case->display();
    }
    else
    {
        cout << "Дело не найдено" << endl;
    }

    const auto not_found_case = office.find_by_case_number("ДЛ-9999-999");
    if (not_found_case)
    {
        not_found_case->display();
    }
    else
    {
        cout << "Дело не найдено" << endl;
    }
    cout << endl;

    // Дополнительные демонстрации
    const auto client_cases = office.find_by_client_name("Максимова Анастасия Олеговна");
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

    const auto family_cases = office.find_by_specialization(Specialization::Family);
    for (const auto& legal_case : family_cases)
    {
        legal_case->display();
    }

    return 0;
}

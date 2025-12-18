#include "../include/LawOffice.h"
#include "../include/CourtCase.h"
#include "../include/ConsultationCase.h"
#include "../include/OfficeLawyer.h"
#include "../include/OfficeClient.h"
#include <gtest/gtest.h>
#include <memory>

using namespace std;

TEST(LawOffice, AddCasesToOffice)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Иванов П.С.", Specialization::Housing, "Высшая");
    auto client1 = make_shared<OfficeClient>("Смирнов В.А.", "+7-999-111-22-33");
    auto client2 = make_shared<OfficeClient>("Козлов И.В.", "+7-999-222-33-44");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-001", "Спор о квартире", lawyer, client1,
        "Районный суд", "15.02.2025", "Подготовка", 150000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-002", "Консультация по наследству", lawyer, client2,
        "Оформление наследства", 2.0, false, 5000.0);

    office.add_case(court);
    office.add_case(consultation);

    EXPECT_EQ(office.size(), 2);
}

TEST(LawOffice, OfficeInitiallyEmpty)
{
    const LawOffice empty_office;
    EXPECT_EQ(empty_office.size(), 0);
}

TEST(LawOffice, FindByCaseNumberExisting)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Сидоров А.Н.", Specialization::Housing, "Первая");
    auto client = make_shared<OfficeClient>("Волков А.П.", "+7-999-333-44-55");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-010", "Жилищный спор", lawyer, client,
        "Городской суд", "20.03.2025", "Слушание", 180000.0);
    office.add_case(court);

    const auto found = office.find_by_case_number("ДЛ-2025-010");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->get_case_number(), "ДЛ-2025-010");
    EXPECT_EQ(found->get_client_name(), "Волков А.П.");
}

TEST(LawOffice, FindByCaseNumberNonExistent)
{
    const LawOffice office;
    const auto found = office.find_by_case_number("ДЛ-9999-999");

    EXPECT_EQ(found, nullptr);
}

TEST(LawOffice, FindByClientNameExisting)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Петрова А.М.", Specialization::Family, "Высшая");
    auto client = make_shared<OfficeClient>("Кузнецова М.И.", "+7-999-444-55-66");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-020", "Бракоразводный процесс", lawyer, client,
        "Центральный суд", "25.02.2025", "Подготовка", 120000.0);
    office.add_case(court);

    const auto found = office.find_by_client_name("Кузнецова М.И.");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_client_name(), "Кузнецова М.И.");
}

TEST(LawOffice, FindByClientNameNonExistent)
{
    const LawOffice office;
    const auto found = office.find_by_client_name("Несуществующий Клиент");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindByClientNameMultiple)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Петрова А.М.", Specialization::Family, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Морозова О.И.", Specialization::Family, "Первая");
    auto client = make_shared<OfficeClient>("Иванова Е.С.", "+7-999-555-66-77");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-030", "Развод", lawyer1, client,
        "Суд", "01.03.2025", "Слушание", 100000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-031", "Консультация по алиментам", lawyer2, client,
        "Алименты", 1.5, true, 4000.0);
    office.add_case(court);
    office.add_case(consultation);

    const auto found = office.find_by_client_name("Иванова Е.С.");

    EXPECT_EQ(found.size(), 2);
}

TEST(LawOffice, FindByLawyerNameExisting)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Сидоров А.Н.", Specialization::Criminal, "Высшая");
    auto client = make_shared<OfficeClient>("Федоров В.В.", "+7-999-666-77-88");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-040", "Уголовное дело", lawyer, client,
        "Городской суд", "10.03.2025", "Апелляция", 250000.0);
    office.add_case(court);

    const auto found = office.find_by_lawyer_name("Сидоров А.Н.");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_lawyer_name(), "Сидоров А.Н.");
}

TEST(LawOffice, FindByLawyerNameNonExistent)
{
    const LawOffice office;
    const auto found = office.find_by_lawyer_name("Несуществующий Адвокат");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindBySpecializationExisting)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Козлова Е.В.", Specialization::Labor, "Первая");
    auto client = make_shared<OfficeClient>("Белова С.Н.", "+7-999-777-88-99");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-050", "Трудовой спор", lawyer, client,
        "Арбитражный суд", "15.03.2025", "Подготовка", 80000.0);
    office.add_case(court);

    const auto found = office.find_by_specialization(Specialization::Labor);

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_specialization(), Specialization::Labor);
}

TEST(LawOffice, FindBySpecializationNonExistent)
{
    const LawOffice office;
    const auto found = office.find_by_specialization(Specialization::Criminal);

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindByServiceTypeCourtCase)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Новиков Д.А.", Specialization::Property, "Высшая");
    auto client = make_shared<OfficeClient>("Орлов И.В.", "+7-999-888-99-00");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-060", "Имущественный спор", lawyer, client,
        "Районный суд", "20.03.2025", "Слушание", 200000.0);
    office.add_case(court);

    const auto found = office.find_by_service_type("Ведение дела в суде");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_service_type(), "Ведение дела в суде");
}

TEST(LawOffice, FindByServiceTypeConsultation)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Иванов П.С.", Specialization::Housing, "Первая");
    auto client = make_shared<OfficeClient>("Соколов А.Д.", "+7-999-000-11-22");

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-070", "Консультация по жилью", lawyer, client,
        "Приватизация", 1.0, true, 4500.0);
    office.add_case(consultation);

    const auto found = office.find_by_service_type("Консультация");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_service_type(), "Консультация");
}

TEST(LawOffice, FindByContentExisting)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Иванов П.С.", Specialization::Housing, "Высшая");
    auto client = make_shared<OfficeClient>("Михайлов К.Л.", "+7-999-111-00-99");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-080", "Спор о праве собственности на квартиру",
        lawyer, client, "Суд", "25.03.2025", "Подготовка", 150000.0);
    office.add_case(court);

    const auto found = office.find_by_content("собственности на квартиру");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_case_number(), "ДЛ-2025-080");
}

TEST(LawOffice, FindByContentNonExistent)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Петров И.П.", Specialization::Housing, "Первая");
    auto client = make_shared<OfficeClient>("Сергеев А.А.", "+7-999-222-11-00");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-090", "Жилищный спор", lawyer, client,
        "Суд", "30.03.2025", "Слушание", 100000.0);
    office.add_case(court);

    const auto found = office.find_by_content("мошенничество");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindActiveCases)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Иванов П.С.", Specialization::Housing, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Петров А.М.", Specialization::Family, "Первая");
    auto client1 = make_shared<OfficeClient>("Клиент А.", "+7-999-333-22-11");
    auto client2 = make_shared<OfficeClient>("Клиент Б.", "+7-999-444-33-22");

    const auto active_court = make_shared<CourtCase>(
        "ДЛ-2025-100", "Активное дело", lawyer1, client1,
        "Суд", "01.04.2025", "Слушание", 100000.0, true);
    const auto inactive_consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-101", "Завершенная консультация", lawyer2, client2,
        "Развод", 1.0, true, 4000.0, false);
    office.add_case(active_court);
    office.add_case(inactive_consultation);

    const auto found = office.find_active_cases();

    ASSERT_EQ(found.size(), 1);
    EXPECT_TRUE(found[0]->get_is_active());
}

TEST(LawOffice, GetServicesWithPrices)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Адвокат 1", Specialization::Housing, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Адвокат 2", Specialization::Family, "Первая");
    auto lawyer3 = make_shared<OfficeLawyer>("Адвокат 3", Specialization::Property, "Высшая");
    auto client1 = make_shared<OfficeClient>("Клиент 1", "+7-999-555-44-33");
    auto client2 = make_shared<OfficeClient>("Клиент 2", "+7-999-666-55-44");
    auto client3 = make_shared<OfficeClient>("Клиент 3", "+7-999-777-66-55");

    const auto court1 = make_shared<CourtCase>(
        "ДЛ-2025-110", "Дело 1", lawyer1, client1,
        "Суд", "01.04.2025", "Подготовка", 100000.0);
    const auto court2 = make_shared<CourtCase>(
        "ДЛ-2025-111", "Дело 2", lawyer2, client2,
        "Суд", "05.04.2025", "Слушание", 200000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-112", "Консультация", lawyer3, client3,
        "Тема", 2.0, false, 5000.0);
    office.add_case(court1);
    office.add_case(court2);
    office.add_case(consultation);

    const auto services = office.get_services_with_prices();

    EXPECT_EQ(services.size(), 2);
}

TEST(LawOffice, GetClientsByService)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Адвокат 1", Specialization::Housing, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Адвокат 2", Specialization::Family, "Первая");
    auto client1 = make_shared<OfficeClient>("Клиент А", "+7-999-888-77-66");
    auto client2 = make_shared<OfficeClient>("Клиент Б", "+7-999-999-88-77");

    const auto court1 = make_shared<CourtCase>(
        "ДЛ-2025-120", "Дело 1", lawyer1, client1,
        "Суд", "10.04.2025", "Подготовка", 100000.0);
    const auto court2 = make_shared<CourtCase>(
        "ДЛ-2025-121", "Дело 2", lawyer2, client2,
        "Суд", "15.04.2025", "Слушание", 150000.0);
    office.add_case(court1);
    office.add_case(court2);

    const auto clients = office.get_clients_by_service("Ведение дела в суде");

    EXPECT_EQ(clients.size(), 2);
}

TEST(LawOffice, GetAvailableLawyers)
{
    LawOffice office;
    auto lawyer1 = OfficeLawyer::create("Иванов П.С.", Specialization::Housing, "Высшая", office);
    auto lawyer2 = OfficeLawyer::create("Петров А.М.", Specialization::Housing, "Первая", office);
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-000-99-88");

    const auto busy_case = make_shared<CourtCase>(
        "ДЛ-2025-130", "Активное дело", lawyer1, client,
        "Суд", "20.04.2025", "Слушание", 100000.0, true);
    lawyer1->add_case(busy_case);
    office.add_case(busy_case);

    const auto available = office.get_available_lawyers(Specialization::Housing);

    ASSERT_EQ(available.size(), 1);
    EXPECT_EQ(available[0], "Петров А.М.");
}

TEST(LawOffice, GetAvailableLawyersNone)
{
    LawOffice office;
    auto lawyer = OfficeLawyer::create("Иванов П.С.", Specialization::Housing, "Высшая", office);
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-111-00-00");

    const auto busy_case = make_shared<CourtCase>(
        "ДЛ-2025-140", "Активное дело", lawyer, client,
        "Суд", "25.04.2025", "Слушание", 100000.0, true);
    lawyer->add_case(busy_case);
    office.add_case(busy_case);

    const auto available = office.get_available_lawyers(Specialization::Housing);

    EXPECT_TRUE(available.empty());
}

// ==================== Тесты CourtCase ====================

TEST(CourtCase, Getters)
{
    auto lawyer = make_shared<OfficeLawyer>("Иванов Петр Сергеевич", Specialization::Housing, "Высшая");
    auto client = make_shared<OfficeClient>("Смирнов Виктор Александрович", "+7-999-222-33-44");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-200", "Спор о собственности", lawyer, client,
        "Московский районный суд", "15.02.2025", "Подготовка к слушанию", 150000.0);

    EXPECT_EQ(court->get_case_number(), "ДЛ-2025-200");
    EXPECT_EQ(court->get_case_content(), "Спор о собственности");
    EXPECT_EQ(court->get_lawyer_name(), "Иванов Петр Сергеевич");
    EXPECT_EQ(court->get_client_name(), "Смирнов Виктор Александрович");
    EXPECT_EQ(court->get_specialization(), Specialization::Housing);
    EXPECT_EQ(court->get_court_name(), "Московский районный суд");
    EXPECT_EQ(court->get_hearing_date(), "15.02.2025");
    EXPECT_EQ(court->get_case_stage(), "Подготовка к слушанию");
    EXPECT_EQ(court->get_service_type(), "Ведение дела в суде");
    EXPECT_DOUBLE_EQ(court->get_service_price(), 150000.0);
    EXPECT_TRUE(court->get_is_active());
}

TEST(CourtCase, ServiceType)
{
    auto lawyer = make_shared<OfficeLawyer>("Адвокат", Specialization::Criminal, "Первая");
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-333-44-55");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-210", "Дело", lawyer, client,
        "Суд", "01.03.2025", "Слушание", 200000.0);

    EXPECT_EQ(court->get_service_type(), "Ведение дела в суде");
}

TEST(ConsultationCase, Getters)
{
    auto lawyer = make_shared<OfficeLawyer>("Новиков Дмитрий Андреевич", Specialization::Property, "Высшая");
    auto client = make_shared<OfficeClient>("Орлов Игорь Васильевич", "+7-999-444-55-66");

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-300", "Консультация по наследству", lawyer, client,
        "Оформление наследства на недвижимость", 2.0, false, 5000.0, false);

    EXPECT_EQ(consultation->get_case_number(), "ДЛ-2025-300");
    EXPECT_EQ(consultation->get_case_content(), "Консультация по наследству");
    EXPECT_EQ(consultation->get_lawyer_name(), "Новиков Дмитрий Андреевич");
    EXPECT_EQ(consultation->get_client_name(), "Орлов Игорь Васильевич");
    EXPECT_EQ(consultation->get_specialization(), Specialization::Property);
    EXPECT_EQ(consultation->get_consultation_topic(), "Оформление наследства на недвижимость");
    EXPECT_DOUBLE_EQ(consultation->get_duration_hours(), 2.0);
    EXPECT_FALSE(consultation->get_is_online());
    EXPECT_DOUBLE_EQ(consultation->get_hourly_rate(), 5000.0);
    EXPECT_EQ(consultation->get_service_type(), "Консультация");
    EXPECT_DOUBLE_EQ(consultation->get_service_price(), 10000.0);
    EXPECT_FALSE(consultation->get_is_active());
}

TEST(ConsultationCase, ServicePriceCalculation)
{
    auto lawyer = make_shared<OfficeLawyer>("Адвокат", Specialization::Family, "Первая");
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-555-66-77");

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-310", "Консультация", lawyer, client,
        "Тема", 3.0, true, 4000.0);

    EXPECT_DOUBLE_EQ(consultation->get_service_price(), 12000.0);
}

TEST(ConsultationCase, OnlineConsultation)
{
    auto lawyer = make_shared<OfficeLawyer>("Адвокат", Specialization::Labor, "Высшая");
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-666-77-88");

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-320", "Онлайн консультация", lawyer, client,
        "Тема", 1.5, true, 3500.0);

    EXPECT_TRUE(consultation->get_is_online());
}

TEST(Polymorphism, IterateThroughOffice)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Адвокат 1", Specialization::Housing, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Адвокат 2", Specialization::Family, "Первая");
    auto client1 = make_shared<OfficeClient>("Клиент 1", "+7-999-777-88-99");
    auto client2 = make_shared<OfficeClient>("Клиент 2", "+7-999-888-99-00");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-400", "Судебное дело", lawyer1, client1,
        "Суд", "01.05.2025", "Подготовка", 100000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-401", "Консультация", lawyer2, client2,
        "Тема", 2.0, false, 5000.0);

    office.add_case(court);
    office.add_case(consultation);

    const auto& all_cases = office.get_all_cases();

    ASSERT_EQ(all_cases.size(), 2);

    for (const auto& legal_case : all_cases)
    {
        EXPECT_NE(legal_case, nullptr);
        EXPECT_FALSE(legal_case->get_case_number().empty());
        EXPECT_FALSE(legal_case->get_client_name().empty());
    }
}

TEST(Polymorphism, VirtualFunctions)
{
    LawOffice office;
    auto lawyer1 = make_shared<OfficeLawyer>("Адвокат 1", Specialization::Criminal, "Высшая");
    auto lawyer2 = make_shared<OfficeLawyer>("Адвокат 2", Specialization::Property, "Первая");
    auto client1 = make_shared<OfficeClient>("Клиент 1", "+7-999-999-00-11");
    auto client2 = make_shared<OfficeClient>("Клиент 2", "+7-999-000-11-22");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-410", "Дело в суде", lawyer1, client1,
        "Суд", "05.05.2025", "Слушание", 250000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-411", "Консультация", lawyer2, client2,
        "Тема", 1.5, true, 4000.0);

    office.add_case(court);
    office.add_case(consultation);

    const auto& all_cases = office.get_all_cases();

    EXPECT_EQ(all_cases[0]->get_service_type(), "Ведение дела в суде");
    EXPECT_EQ(all_cases[1]->get_service_type(), "Консультация");
}

TEST(EdgeCases, EmptyStringSearch)
{
    const LawOffice office;

    const auto found_by_number = office.find_by_case_number("");
    EXPECT_EQ(found_by_number, nullptr);

    const auto found_by_client = office.find_by_client_name("");
    EXPECT_TRUE(found_by_client.empty());
}

TEST(EdgeCases, SpecializationToString)
{
    EXPECT_EQ(specialization_to_string(Specialization::Housing), "Жилищные дела");
    EXPECT_EQ(specialization_to_string(Specialization::Family), "Семейные дела");
    EXPECT_EQ(specialization_to_string(Specialization::Criminal), "Уголовные дела");
    EXPECT_EQ(specialization_to_string(Specialization::Labor), "Трудовые споры");
    EXPECT_EQ(specialization_to_string(Specialization::Property), "Имущественные споры");
}

TEST(EdgeCases, SetIsActive)
{
    auto lawyer = make_shared<OfficeLawyer>("Адвокат", Specialization::Housing, "Высшая");
    auto client = make_shared<OfficeClient>("Клиент", "+7-999-111-22-33");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-500", "Дело", lawyer, client,
        "Суд", "10.05.2025", "Подготовка", 100000.0, true);

    EXPECT_TRUE(court->get_is_active());

    court->set_is_active(false);
    EXPECT_FALSE(court->get_is_active());

    court->set_is_active(true);
    EXPECT_TRUE(court->get_is_active());
}

TEST(Integration, CompleteWorkflow)
{
    LawOffice office;

    // Регистрация адвокатов
    auto lawyer1 = OfficeLawyer::create("Иванов П.С.", Specialization::Housing, "Высшая", office);
    auto lawyer2 = OfficeLawyer::create("Петрова А.М.", Specialization::Family, "Первая", office);

    // Регистрация клиентов
    auto client1 = OfficeClient::create("Клиент А", "+7-999-222-33-44", office);
    auto client2 = OfficeClient::create("Клиент Б", "+7-999-333-44-55", office);

    // Добавление дел
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-600", "Жилищный спор", lawyer1, client1,
        "Районный суд", "15.05.2025", "Подготовка", 150000.0);
    lawyer1->add_case(court);
    client1->add_case(court);
    office.add_case(court);

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-601", "Консультация по разводу", lawyer2, client2,
        "Процедура развода", 1.5, false, 5000.0, false);
    lawyer2->add_case(consultation);
    client2->add_case(consultation);
    office.add_case(consultation);

    // Проверка поиска по номеру дела
    const auto by_number = office.find_by_case_number("ДЛ-2025-600");
    ASSERT_NE(by_number, nullptr);
    EXPECT_EQ(by_number->get_case_content(), "Жилищный спор");

    // Проверка поиска клиентов по услуге
    const auto court_clients = office.get_clients_by_service("Ведение дела в суде");
    EXPECT_EQ(court_clients.size(), 1);

    // Проверка свободных адвокатов
    const auto available_housing = office.get_available_lawyers(Specialization::Housing);
    EXPECT_TRUE(available_housing.empty());

    const auto available_family = office.get_available_lawyers(Specialization::Family);
    EXPECT_EQ(available_family.size(), 1);

    // Проверка списка услуг
    const auto services = office.get_services_with_prices();
    EXPECT_EQ(services.size(), 2);
}

TEST(Person, AbstractClassHierarchy)
{
    auto lawyer = make_shared<OfficeLawyer>("Иванов Иван Иванович", Specialization::Housing, "Высшая");
    auto client = make_shared<OfficeClient>("Петров Петр Петрович", "+7-999-444-55-66");

    shared_ptr<Person> person1 = lawyer;
    shared_ptr<Person> person2 = client;

    EXPECT_EQ(person1->get_role(), "Адвокат");
    EXPECT_EQ(person2->get_role(), "Клиент");
    EXPECT_EQ(person1->get_full_name(), "Иванов Иван Иванович");
    EXPECT_EQ(person2->get_full_name(), "Петров Петр Петрович");
}

TEST(Client, CasesManagement)
{
    auto lawyer = make_shared<OfficeLawyer>("Ефимов Егор Иванович", Specialization::Housing, "Высшая");
    auto client = make_shared<OfficeClient>("Сидоров Сидор Сидорович", "+7-999-555-66-77");

    const auto court1 = make_shared<CourtCase>(
        "ДЛ-2024-001", "Дело 1", lawyer, client,
        "Суд", "01.01.2024", "Подготовка", 50000.0);
    const auto court2 = make_shared<CourtCase>(
        "ДЛ-2024-002", "Дело 2", lawyer, client,
        "Суд", "02.01.2024", "Слушание", 100000.0);

    client->add_case(court1);
    client->add_case(court2);

    const auto cases = client->get_cases();
    EXPECT_EQ(cases.size(), 2);
}

TEST(Lawyer, CasesManagement)
{
    auto lawyer = make_shared<OfficeLawyer>("Петров Петр Петрович", Specialization::Family, "Высшая");
    auto client1 = make_shared<OfficeClient>("Иванов Иван Иванович", "+7-999-666-77-88");
    auto client2 = make_shared<OfficeClient>("Сидоров Сидор Сидорович", "+7-999-777-88-99");

    const auto court = make_shared<CourtCase>(
        "ДЛ-2024-001", "Дело 1", lawyer, client1,
        "Суд", "01.01.2024", "Подготовка", 50000.0);

    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2024-002", "Консультация", lawyer, client2,
        "Тема", 2.0, false, 5000.0);

    lawyer->add_case(court);
    lawyer->add_case(consultation);

    const auto cases = lawyer->get_cases();
    EXPECT_EQ(cases.size(), 2);
    EXPECT_EQ(lawyer->get_category(), "Высшая");
}

TEST(FactoryMethods, CreateLawyer)
{
    LawOffice office;
    auto lawyer = OfficeLawyer::create("Тестов Тест Тестович", Specialization::Housing, "Высшая", office);

    EXPECT_EQ(office.get_all_lawyers().size(), 1);
    EXPECT_EQ(lawyer->get_full_name(), "Тестов Тест Тестович");
    EXPECT_EQ(lawyer->get_category(), "Высшая");
}

TEST(FactoryMethods, CreateClient)
{
    LawOffice office;
    auto client = OfficeClient::create("Клиентов Клиент Клиентович", "+7-999-888-99-00", office);

    EXPECT_EQ(office.get_all_clients().size(), 1);
    EXPECT_EQ(client->get_full_name(), "Клиентов Клиент Клиентович");
    EXPECT_EQ(client->get_client_type(), "Клиент конторы");
}

TEST(FactoryMethods, CreateCase)
{
    LawOffice office;
    auto lawyer = make_shared<OfficeLawyer>("Адвокатов Адвокат Адвокатович", Specialization::Housing, "Первая");
    auto client = make_shared<OfficeClient>("Клиентов Клиент Клиентович", "+7-999-999-00-11");

    auto court = CourtCase::create("ДЛ-2024-999", "Тестовое дело", lawyer, client,
                                   "Суд", "01.01.2024", "Подготовка", 12345.0, office);

    EXPECT_EQ(office.size(), 1);
    EXPECT_EQ(court->get_case_number(), "ДЛ-2024-999");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

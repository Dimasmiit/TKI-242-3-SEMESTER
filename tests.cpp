#include "LawOffice.h"
#include "CourtCase.h"
#include "ConsultationCase.h"
#include <gtest/gtest.h>
#include <memory>

using namespace std;

// ==================== Тесты LawOffice ====================

TEST(LawOffice, AddCasesToOffice)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-001", "Спор о квартире", "Иванов П.С.", "Смирнов В.А.",
        Specialization::Housing, "Районный суд", "15.02.2025", "Подготовка", 150000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-002", "Консультация по наследству", "Петров А.М.", "Козлов И.В.",
        Specialization::Property, "Оформление наследства", 2.0, false, 5000.0);

    office.add_case(court);
    office.add_case(consultation);

    EXPECT_EQ(office.size(), 2);
}

TEST(LawOffice, OfficeInitiallyEmpty)
{
    LawOffice empty_office;
    EXPECT_EQ(empty_office.size(), 0);
}

TEST(LawOffice, FindByCaseNumberExisting)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-010", "Жилищный спор", "Сидоров А.Н.", "Волков А.П.",
        Specialization::Housing, "Городской суд", "20.03.2025", "Слушание", 180000.0);
    office.add_case(court);

    const auto found = office.find_by_case_number("ДЛ-2025-010");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->get_case_number(), "ДЛ-2025-010");
    EXPECT_EQ(found->get_client_name(), "Волков А.П.");
}

TEST(LawOffice, FindByCaseNumberNonExistent)
{
    LawOffice office;
    const auto found = office.find_by_case_number("ДЛ-9999-999");

    EXPECT_EQ(found, nullptr);
}

TEST(LawOffice, FindByClientNameExisting)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-020", "Бракоразводный процесс", "Петрова А.М.", "Кузнецова М.И.",
        Specialization::Family, "Центральный суд", "25.02.2025", "Подготовка", 120000.0);
    office.add_case(court);

    const auto found = office.find_by_client_name("Кузнецова М.И.");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_client_name(), "Кузнецова М.И.");
}

TEST(LawOffice, FindByClientNameNonExistent)
{
    LawOffice office;
    const auto found = office.find_by_client_name("Несуществующий Клиент");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindByClientNameMultiple)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-030", "Развод", "Петрова А.М.", "Иванова Е.С.",
        Specialization::Family, "Суд", "01.03.2025", "Слушание", 100000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-031", "Консультация по алиментам", "Морозова О.И.", "Иванова Е.С.",
        Specialization::Family, "Алименты", 1.5, true, 4000.0);
    office.add_case(court);
    office.add_case(consultation);

    const auto found = office.find_by_client_name("Иванова Е.С.");

    EXPECT_EQ(found.size(), 2);
}

TEST(LawOffice, FindByLawyerNameExisting)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-040", "Уголовное дело", "Сидоров А.Н.", "Федоров В.В.",
        Specialization::Criminal, "Городской суд", "10.03.2025", "Апелляция", 250000.0);
    office.add_case(court);

    const auto found = office.find_by_lawyer_name("Сидоров А.Н.");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_lawyer_name(), "Сидоров А.Н.");
}

TEST(LawOffice, FindByLawyerNameNonExistent)
{
    LawOffice office;
    const auto found = office.find_by_lawyer_name("Несуществующий Адвокат");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindBySpecializationExisting)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-050", "Трудовой спор", "Козлова Е.В.", "Белова С.Н.",
        Specialization::Labor, "Арбитражный суд", "15.03.2025", "Подготовка", 80000.0);
    office.add_case(court);

    const auto found = office.find_by_specialization(Specialization::Labor);

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_specialization(), Specialization::Labor);
}

TEST(LawOffice, FindBySpecializationNonExistent)
{
    LawOffice office;
    const auto found = office.find_by_specialization(Specialization::Criminal);

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindByServiceTypeCourtCase)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-060", "Имущественный спор", "Новиков Д.А.", "Орлов И.В.",
        Specialization::Property, "Районный суд", "20.03.2025", "Слушание", 200000.0);
    office.add_case(court);

    const auto found = office.find_by_service_type("Ведение дела в суде");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_service_type(), "Ведение дела в суде");
}

TEST(LawOffice, FindByServiceTypeConsultation)
{
    LawOffice office;
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-070", "Консультация по жилью", "Иванов П.С.", "Соколов А.Д.",
        Specialization::Housing, "Приватизация", 1.0, true, 4500.0);
    office.add_case(consultation);

    const auto found = office.find_by_service_type("Консультация");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_service_type(), "Консультация");
}

TEST(LawOffice, FindByContentExisting)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-080", "Спор о праве собственности на квартиру",
        "Иванов П.С.", "Михайлов К.Л.",
        Specialization::Housing, "Суд", "25.03.2025", "Подготовка", 150000.0);
    office.add_case(court);

    const auto found = office.find_by_content("собственности на квартиру");

    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->get_case_number(), "ДЛ-2025-080");
}

TEST(LawOffice, FindByContentNonExistent)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-090", "Жилищный спор", "Петров И.П.", "Сергеев А.А.",
        Specialization::Housing, "Суд", "30.03.2025", "Слушание", 100000.0);
    office.add_case(court);

    const auto found = office.find_by_content("мошенничество");

    EXPECT_TRUE(found.empty());
}

TEST(LawOffice, FindActiveCases)
{
    LawOffice office;
    const auto active_court = make_shared<CourtCase>(
        "ДЛ-2025-100", "Активное дело", "Иванов П.С.", "Клиент А.",
        Specialization::Housing, "Суд", "01.04.2025", "Слушание", 100000.0, true);
    const auto inactive_consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-101", "Завершенная консультация", "Петров А.М.", "Клиент Б.",
        Specialization::Family, "Развод", 1.0, true, 4000.0, false);
    office.add_case(active_court);
    office.add_case(inactive_consultation);

    const auto found = office.find_active_cases();

    ASSERT_EQ(found.size(), 1);
    EXPECT_TRUE(found[0]->get_is_active());
}

TEST(LawOffice, GetServicesWithPrices)
{
    LawOffice office;
    const auto court1 = make_shared<CourtCase>(
        "ДЛ-2025-110", "Дело 1", "Адвокат 1", "Клиент 1",
        Specialization::Housing, "Суд", "01.04.2025", "Подготовка", 100000.0);
    const auto court2 = make_shared<CourtCase>(
        "ДЛ-2025-111", "Дело 2", "Адвокат 2", "Клиент 2",
        Specialization::Family, "Суд", "05.04.2025", "Слушание", 200000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-112", "Консультация", "Адвокат 3", "Клиент 3",
        Specialization::Property, "Тема", 2.0, false, 5000.0);
    office.add_case(court1);
    office.add_case(court2);
    office.add_case(consultation);

    const auto services = office.get_services_with_prices();

    EXPECT_EQ(services.size(), 2);
}

TEST(LawOffice, GetClientsByService)
{
    LawOffice office;
    const auto court1 = make_shared<CourtCase>(
        "ДЛ-2025-120", "Дело 1", "Адвокат 1", "Клиент А",
        Specialization::Housing, "Суд", "10.04.2025", "Подготовка", 100000.0);
    const auto court2 = make_shared<CourtCase>(
        "ДЛ-2025-121", "Дело 2", "Адвокат 2", "Клиент Б",
        Specialization::Family, "Суд", "15.04.2025", "Слушание", 150000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-122", "Консультация", "Адвокат 3", "Клиент В",
        Specialization::Property, "Тема", 1.5, true, 4000.0);
    office.add_case(court1);
    office.add_case(court2);
    office.add_case(consultation);

    const auto court_clients = office.get_clients_by_service("Ведение дела в суде");
    const auto consultation_clients = office.get_clients_by_service("Консультация");

    EXPECT_EQ(court_clients.size(), 2);
    EXPECT_EQ(consultation_clients.size(), 1);
}

TEST(LawOffice, GetAvailableLawyers)
{
    LawOffice office;
    office.register_lawyer("Иванов П.С.", Specialization::Housing);
    office.register_lawyer("Петров А.М.", Specialization::Housing);
    
    const auto busy_case = make_shared<CourtCase>(
        "ДЛ-2025-130", "Активное дело", "Иванов П.С.", "Клиент",
        Specialization::Housing, "Суд", "20.04.2025", "Слушание", 100000.0, true);
    office.add_case(busy_case);

    const auto available = office.get_available_lawyers(Specialization::Housing);

    ASSERT_EQ(available.size(), 1);
    EXPECT_EQ(available[0], "Петров А.М.");
}

TEST(LawOffice, GetAvailableLawyersNone)
{
    LawOffice office;
    office.register_lawyer("Иванов П.С.", Specialization::Housing);
    
    const auto busy_case = make_shared<CourtCase>(
        "ДЛ-2025-140", "Активное дело", "Иванов П.С.", "Клиент",
        Specialization::Housing, "Суд", "25.04.2025", "Слушание", 100000.0, true);
    office.add_case(busy_case);

    const auto available = office.get_available_lawyers(Specialization::Housing);

    EXPECT_TRUE(available.empty());
}

// ==================== Тесты CourtCase ====================

TEST(CourtCase, Getters)
{
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-200", "Спор о собственности", "Иванов Петр Сергеевич",
        "Смирнов Виктор Александрович", Specialization::Housing,
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
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-210", "Дело", "Адвокат", "Клиент",
        Specialization::Criminal, "Суд", "01.03.2025", "Слушание", 200000.0);

    EXPECT_EQ(court->get_service_type(), "Ведение дела в суде");
}

// ==================== Тесты ConsultationCase ====================

TEST(ConsultationCase, Getters)
{
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-300", "Консультация по наследству", "Новиков Дмитрий Андреевич",
        "Орлов Игорь Васильевич", Specialization::Property,
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
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-310", "Консультация", "Адвокат", "Клиент",
        Specialization::Family, "Тема", 3.0, true, 4000.0);

    EXPECT_DOUBLE_EQ(consultation->get_service_price(), 12000.0);
}

TEST(ConsultationCase, OnlineConsultation)
{
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-320", "Онлайн консультация", "Адвокат", "Клиент",
        Specialization::Labor, "Тема", 1.5, true, 3500.0);

    EXPECT_TRUE(consultation->get_is_online());
}

// ==================== Тесты полиморфизма ====================

TEST(Polymorphism, IterateThroughOffice)
{
    LawOffice office;
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-400", "Судебное дело", "Адвокат 1", "Клиент 1",
        Specialization::Housing, "Суд", "01.05.2025", "Подготовка", 100000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-401", "Консультация", "Адвокат 2", "Клиент 2",
        Specialization::Family, "Тема", 2.0, false, 5000.0);

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
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-410", "Дело в суде", "Адвокат 1", "Клиент 1",
        Specialization::Criminal, "Суд", "05.05.2025", "Слушание", 250000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-411", "Консультация", "Адвокат 2", "Клиент 2",
        Specialization::Property, "Тема", 1.5, true, 4000.0);

    office.add_case(court);
    office.add_case(consultation);

    const auto& all_cases = office.get_all_cases();

    EXPECT_EQ(all_cases[0]->get_service_type(), "Ведение дела в суде");
    EXPECT_EQ(all_cases[1]->get_service_type(), "Консультация");
}

// ==================== Тесты граничных случаев ====================

TEST(EdgeCases, EmptyStringSearch)
{
    LawOffice office;

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
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-500", "Дело", "Адвокат", "Клиент",
        Specialization::Housing, "Суд", "10.05.2025", "Подготовка", 100000.0, true);

    EXPECT_TRUE(court->get_is_active());
    
    court->set_is_active(false);
    EXPECT_FALSE(court->get_is_active());
    
    court->set_is_active(true);
    EXPECT_TRUE(court->get_is_active());
}

// ==================== Интеграционные тесты ====================

TEST(Integration, CompleteWorkflow)
{
    LawOffice office;

    // Регистрация адвокатов
    office.register_lawyer("Иванов П.С.", Specialization::Housing);
    office.register_lawyer("Петрова А.М.", Specialization::Family);

    // Добавление дел
    const auto court = make_shared<CourtCase>(
        "ДЛ-2025-600", "Жилищный спор", "Иванов П.С.", "Клиент А",
        Specialization::Housing, "Районный суд", "15.05.2025", "Подготовка", 150000.0);
    const auto consultation = make_shared<ConsultationCase>(
        "ДЛ-2025-601", "Консультация по разводу", "Петрова А.М.", "Клиент Б",
        Specialization::Family, "Процедура развода", 1.5, false, 5000.0, false);
    
    office.add_case(court);
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

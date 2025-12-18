#pragma once

#include "../include/Client.h"

class LawOffice;

/**
 * @brief Класс OfficeClient представляет клиента адвокатской конторы.
 */
class OfficeClient : public Client
{
private:
    string phone_number; // Номер телефона клиента

public:
    /**
     * @brief Конструктор клиента конторы.
     * @param full_name ФИО клиента.
     * @param phone_number Номер телефона.
     */
    OfficeClient(const string& full_name, const string& phone_number);

    /**
     * @brief Фабричный метод для создания клиента с регистрацией в конторе.
     * @param full_name ФИО клиента.
     * @param phone_number Номер телефона.
     * @param office Ссылка на контору.
     * @return shared_ptr на созданного клиента.
     */
    static shared_ptr<OfficeClient> create(const string& full_name, 
                                            const string& phone_number,
                                            LawOffice& office);

    /**
     * @brief Выводит информацию о клиенте.
     */
    void display() const override;

    /**
     * @brief Возвращает тип клиента.
     * @return Строка с типом клиента.
     */
    string get_client_type() const override;

    /**
     * @brief Получает номер телефона клиента.
     * @return Номер телефона.
     */
    string get_phone_number() const;
};

#pragma once

#include "../include/Lawyer.h"

class LawOffice;

/**
 * @brief Класс OfficeLawyer представляет адвоката адвокатской конторы.
 */
class OfficeLawyer : public Lawyer
{
private:
    string category; // Категория адвоката (например, "Высшая", "Первая")

public:
    /**
     * @brief Конструктор адвоката конторы.
     * @param full_name ФИО адвоката.
     * @param specialization Специализация адвоката.
     * @param category Категория адвоката.
     */
    OfficeLawyer(const string& full_name, const Specialization specialization, 
                 const string& category);

    /**
     * @brief Фабричный метод для создания адвоката с регистрацией в конторе.
     * @param full_name ФИО адвоката.
     * @param specialization Специализация адвоката.
     * @param category Категория адвоката.
     * @param office Ссылка на контору.
     * @return shared_ptr на созданного адвоката.
     */
    static shared_ptr<OfficeLawyer> create(const string& full_name, 
                                           const Specialization specialization,
                                           const string& category, 
                                           LawOffice& office);

    /**
     * @brief Выводит информацию об адвокате.
     */
    void display() const override;

    /**
     * @brief Возвращает категорию адвоката.
     * @return Строка с категорией.
     */
    string get_category() const override;
};

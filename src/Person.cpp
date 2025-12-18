#include "../include/Person.h"

Person::Person(const string& full_name)
    : full_name(full_name) {}

string Person::get_full_name() const
{
    return full_name;
}

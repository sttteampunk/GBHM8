#include "Person.hpp"

Person::Person()
    : last_name(""), first_name(""), patronymic(std::nullopt) {}

Person::Person(std::string l_name, std::string f_name)
    : last_name(l_name), first_name(f_name), patronymic(std::nullopt) {}

Person::Person(std::string l_name, std::string f_name, std::string patr)
    : last_name{ std::move(l_name) }, first_name{ std::move(f_name) }, patronymic{ std::move(patr) } {}

std::string Person::GetFirstName() const { return first_name; }

std::optional<std::string> Person::GetPatronymic() const { return patronymic; }

std::string Person::GetLastName() const { return last_name; }

Person Person::ReadFromStream(std::istringstream& iss) {
    Person person;
    constexpr int IGNORE_NUM = 1;
    std::string temp;
    if (iss.peek() == ' ')
        iss.ignore(IGNORE_NUM);
    iss >> person.last_name >> person.first_name >> temp;
    if (temp != "-")
        person.patronymic.emplace(temp);
    return person;
}

void Person::SetPerson(std::istringstream& iss) {
    std::string temp;
    iss >> last_name >> first_name >> temp;
    if (temp == "-")
        return;
    else
        patronymic.emplace(temp);
}

std::ostream& operator<< (std::ostream& out, const Person& person) {
    out << person.last_name << ' ' << person.first_name;
    if (person.patronymic.has_value())
        out << ' ' << person.patronymic.value();
    return out;
}

bool operator< (const Person& lhs, const Person& rhs) {
    return std::tie(lhs.last_name, lhs.first_name, lhs.patronymic) <
        std::tie(rhs.last_name, rhs.first_name, rhs.patronymic);
}

bool operator== (const Person& lhs, const Person& rhs) {
    return std::tie(lhs.last_name, lhs.first_name, lhs.patronymic) ==
        std::tie(rhs.last_name, rhs.first_name, rhs.patronymic);
}
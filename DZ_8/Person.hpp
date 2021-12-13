#pragma once

#include <tuple>
#include <optional>
#include <iostream>
#include <string>
#include <sstream>

class Person {
public:
    Person();

    Person(std::string l_name, std::string f_name);

    Person(std::string l_name, std::string f_name, std::string patr);

    std::string GetFirstName() const;

    std::optional<std::string> GetPatronymic() const;

    std::string GetLastName() const;

    static Person ReadFromStream(std::istringstream& iss);

    void SetPerson(std::istringstream& iss);

    friend std::ostream& operator<< (std::ostream& out, const Person& person);

    friend bool operator< (const Person& lhs, const Person& rhs);

    friend bool operator== (const Person& lhs, const Person& rhs);

private:
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronymic;
};
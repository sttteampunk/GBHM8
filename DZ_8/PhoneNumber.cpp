#include "PhoneNumber.hpp"

PhoneNumber::PhoneNumber()
    : country_code(0), city_code(0), number("0000000"), add_number(std::nullopt) {}

PhoneNumber::PhoneNumber(int country, int city, std::string num, std::optional<int> add_num)
    : country_code{ country }, city_code{ city }, number{ std::move(num) }, add_number{ add_num } {}

PhoneNumber::PhoneNumber(int country, int city, std::string num)
    : country_code{ country }, city_code{ city }, number{ std::move(num) } {}

int PhoneNumber::getCountryCode() const {
    return country_code;
}

int PhoneNumber::GetCityCode() const {
    return city_code;
}

std::string PhoneNumber::GetNumber() const {
    return number;
}

std::optional<int> PhoneNumber::GetAddNumber() const {
    if (const int add_num = add_number.value())
        return add_num;
    else
        return add_number;
}

PhoneNumber PhoneNumber::ReadFromStream(std::istringstream& iss) {
    PhoneNumber phonenumb;
    constexpr int IGNORE_NUM = 1;
    if (iss.peek() == ' ')
        iss.ignore(IGNORE_NUM);
    iss >> phonenumb.country_code >> phonenumb.city_code >>
        phonenumb.number;
    if (iss.peek() != '-') {
        iss >> phonenumb.add_number.emplace();
    }
    return phonenumb;
}

void PhoneNumber::SetPhoneNumber(std::istringstream& iss) {
    std::string temp;
    iss >> country_code >> city_code >> number >> temp;

    if (temp == "-")
        return;
    else
        add_number.emplace(std::stoi(temp));
}

std::ostream& operator<< (std::ostream& out, const PhoneNumber& phone_number) {
    out << '+' << phone_number.getCountryCode() << " (" << phone_number.GetCityCode() << ") " <<
        phone_number.GetNumber() << ' ';
    if (phone_number.add_number.has_value()) {
        out << phone_number.add_number.value();
    }
    return out;
}

bool operator< (const PhoneNumber& num1, const PhoneNumber& num2) {
    return std::tie(num1.country_code, num1.city_code, num1.number, num1.add_number) <
        std::tie(num2.country_code, num2.city_code, num2.number, num2.add_number);
}
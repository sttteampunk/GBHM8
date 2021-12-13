#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <optional>
#include <tuple>

class PhoneNumber {
public:
    PhoneNumber();

    PhoneNumber(int country, int city, std::string num, std::optional<int> add_num);

    PhoneNumber(int country, int city, std::string num);

    int getCountryCode() const;

    int GetCityCode() const;

    std::string GetNumber() const;

    std::optional<int> GetAddNumber() const;

    static PhoneNumber ReadFromStream(std::istringstream& iss);

    void SetPhoneNumber(std::istringstream& iss);

    friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& phone_number);

    friend bool operator< (const PhoneNumber& num1, const PhoneNumber& num2);

private:
    int country_code;
    int city_code;
    std::string number;
    std::optional<int> add_number;
};
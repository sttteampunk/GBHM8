#include "PhoneBook.hpp"

PhoneBook::PhoneBook(std::ifstream& file)
{
    FileToObj(file);
    if (!file)
        std::cerr << "Cannot open the file\n";
}

PhoneBook::~PhoneBook() {
}

void PhoneBook::FileToObj(std::ifstream& file) {

    while (!file.eof()) {
        std::getline(file, string);
        std::istringstream istringstr(string);
        Person person;
        PhoneNumber number;
        person.SetPerson(istringstr);
        number.SetPhoneNumber(istringstr);
        phone_book.push_back(std::make_pair(person, number));
    }
}

void PhoneBook::SortByName() {
    std::sort(phone_book.begin(), phone_book.end(), [](std::pair<Person, PhoneNumber> lhs,
        std::pair<Person, PhoneNumber> rhs) {
            return lhs.first < rhs.first;
        });
}

void PhoneBook::SortByPhone() {
    std::sort(phone_book.begin(), phone_book.end(), [](std::pair<Person, PhoneNumber> lhs,
        std::pair<Person, PhoneNumber> rhs) {
            return lhs.second < rhs.second;
        });
}

std::tuple<std::string, PhoneNumber>
PhoneBook::GetPhoneNumber(const std::string& surname) {
    size_t count = 0;
    const PhoneNumber* number{};
    auto lambda = [&](auto& entry) {
        if (entry.first.GetLastName() == surname) {
            count++;
            number = &entry.second;
        }
    };
    std::for_each(phone_book.begin(), phone_book.end(), lambda);
    if (count == 0)
        return { "None found!", {} };
    else if (count > 1)
        return { "Found more than one!", *number };
    return { "", *number };
}

void PhoneBook::ChangePhoneNumber(const Person& person, PhoneNumber new_num) {
    auto user = std::find_if(phone_book.begin(), phone_book.end(), [&person](std::pair<Person, PhoneNumber>& user) {
        return user.first == person;
        });

    if (user != phone_book.end())
        user->second = new_num;
}

std::ostream& operator<< (std::ostream& out, PhoneBook& book) {
    for (const auto& iter : book.phone_book) {
        out << iter.first << ' ' << iter.second << std::endl;
    }
    return out;
}
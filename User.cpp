//
// Created by ahmed on 17/12/2023.
//

#include "User.h"

User::User() {

}

User::User(int id, const std::string &user_name, const std::string &full_name, const std::string &password,
           const std::string &email, bool allow_anonymous) : id(id),
                                                             user_name(user_name), full_name(full_name), email(email),
                                                             allow_anonymous(allow_anonymous) {
}

int User::getUserId() const {
    return id;
}

const std::string &User::getUserName() const {
    return user_name;
}

const std::string &User::getFullName() const {
    return full_name;
}

const std::string &User::getPassword() const {
    return password;
}

const std::string &User::getEmail() const {
    return email;
}

const bool &User::getAllowAnonymous() const {
    return allow_anonymous;
}

bool User::checkPassword(const std::string &password) const {
    return getPassword() == password;
}

void User::print() const {
    std::cout << "ID: " << getUserId() << "\tName: " << getFullName() << "\n";
}



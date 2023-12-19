//
// Created by ahmed on 17/12/2023.
//
#include <string>
#include <fstream>
#include <iostream>

#ifndef ASKME_USING_C__OPP_USER_H
#define ASKME_USING_C__OPP_USER_H


class User {
private:
    int id;
    std::string user_name, full_name, password, email;
    bool allow_anonymous;
public:
    User();

    User(int id, const std::string &user_name, const std::string &full_name,
         const std::string &password, const std::string &email, bool allow_anonymous);

    int getUserId() const;

    const std::string &getUserName() const;

    const std::string &getFullName() const;

    const std::string &getPassword() const;

    const std::string &getEmail() const;

    const bool &getAllowAnonymous() const;

    bool checkPassword(const std::string &password) const;

    void print() const;
};


#endif //ASKME_USING_C__OPP_USER_H

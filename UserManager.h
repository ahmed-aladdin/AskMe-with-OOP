//
// Created by ahmed on 17/12/2023.
//
#include "User.h"
#include "QuestionManager.h"
#include <unordered_map>
#include <fstream>

#ifndef ASKME_USING_C__OPP_USERMANAGER_H
#define ASKME_USING_C__OPP_USERMANAGER_H


class UserManager {
private:
    QuestionManager question_manager;
    int number_of_users, next_id;
    std::unordered_map<std::string, User *> users_by_name;
    std::unordered_map<int, User *> users_by_id;
public:
    UserManager();
    ~UserManager();
    void loadData() ;

    void saveData() ;

    void logIn();

    void signUp();

    static void menuList() ;

    void userMenu(User *current_user);

    User *addUser(const std::string &user_name, const std::string &full_name,
                  const std::string &password, const std::string &email, bool allow_anonymous) ;

    User *getUserById(int user_id) const;

    User *getUserByUserName(const std::string &user_name) const;

    void listSystemUsers() const;
};


#endif //ASKME_USING_C__OPP_USERMANAGER_H

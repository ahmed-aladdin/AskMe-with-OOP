//
// Created by ahmed on 17/12/2023.
//

#include "UserManager.h"

UserManager::UserManager() {
    next_id = number_of_users = 0;
}

UserManager::~UserManager() {
    for (auto &[id, user]: users_by_id) {
        delete user;
        user = nullptr;
    }
    users_by_name.clear();
    users_by_id.clear();
}

void UserManager::loadData() {
    question_manager.loadData();
    std::ifstream user_file("UserData.txt");
    if (!user_file.is_open()) {
        std::cout << "Error: Can't open file named 'UserData.txt'\n";
        return;
    }
    int id;
    std::string user_name, full_name, password, email;
    bool allow_anonymous;

    user_file >> number_of_users >> next_id;
    for (int i = 0; i < number_of_users; ++i) {


        user_file >> id >> user_name >> full_name
                  >> password >> email >> allow_anonymous;

        User *user = new User(id, user_name, full_name, password, email, allow_anonymous);

        users_by_name[user_name] = user;
        users_by_id[id] = user;
    }
}

void UserManager::saveData() {
    question_manager.saveData();
    std::ofstream user_file("UserData.txt");
    if (!user_file.is_open()) {
        std::cout << "Error: Can't open file named 'UserData.txt'\n";
        return;
    }
    user_file << number_of_users << " " << next_id << "\n";
    for (auto &[id, user]: users_by_id) {

        user_file << user->getUserId() << " " << user->getUserName() << " " << user->getFullName() << " "
                  << user->getPassword() << " " << user->getEmail() << " " << user->getAllowAnonymous() << "\n";
    }
}

void UserManager::logIn() {
    std::string user_name, password;
    std::cout << "Enter user name. (no spaces): ";
    std::cin >> user_name;
    std::cout << "Enter password. (no spaces): ";
    std::cin >> password;
    User *user = getUserByUserName(user_name);
    if (user == nullptr || user->checkPassword(password)) {
        std::cout << "Invalid sign in, wrong with user name or password.\n";
        return;
    }
    userMenu(user);
}

void UserManager::signUp() {
    std::string user_name, full_name, password, email;
    int allow_anonymous;
    while (true) {
        std::cout << "Enter user name. (no spaces):";
        std::cin >> user_name;
        if (getUserByUserName(user_name) == nullptr)
            break;
        std::cout << "Try again...this user name is in use.\n";
    }
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter name: ";
    std::cin.ignore();
    getline(std::cin, full_name);
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Allow anonymous question? (0 for no,otherwise for yes): ";
    std::cin >> allow_anonymous;

    User *user = addUser(user_name, full_name,
                         password, email, (bool) allow_anonymous);
    userMenu(user);
}

void UserManager::menuList() {
    std::cout << "\nMenu:\n";
    std::cout << "\t1: Print Questions To Me.\n";
    std::cout << "\t2: Print Questions From Me.\n";
    std::cout << "\t3: Answer Question.\n";
    std::cout << "\t4: Delete Question.\n";
    std::cout << "\t5: Ask Question.\n";
    std::cout << "\t6: List System Users.\n";
    std::cout << "\t7: Feed.\n";
    std::cout << "\t8: Logout.\n";
}

void UserManager::userMenu(User *current_user) {
    menuList();
    int value;
    do {
        std::cout << "\nEnter number in range 1 - 8, or enter 9 for menu : ";
        std::cin >> value;

        if (value == 1) {
            question_manager.printQuestionsToMe(current_user->getUserId());

        } else if (value == 2) {
            question_manager.printQuestionsFromMe(current_user->getUserId());

        } else if (value == 3) {
            question_manager.answerQuestion(current_user->getUserId());

        } else if (value == 4) {
            question_manager.deleteQuestion(current_user->getUserId());
        } else if (value == 5) {

            int to, from = current_user->getUserId();

            while (true) {
                std::cout << "Enter user id or -1 for cancel: ";
                std::cin >> to;
                if (to == -1)break;
                if (getUserById(to) == nullptr) {
                    std::cout << "Sorry! user id doesn't exist.\n";
                } else
                    break;
            }
            //when -1 cancel
            if (to != -1)
                question_manager.askQuestion(from, to, getUserById(to)->getAllowAnonymous());

        } else if (value == 6) {
            listSystemUsers();
        } else if (value == 7) {
            question_manager.feed();
        } else if (value == 8) {
            std::cout << "\nLogging out...\n";
        } else if (value == 9) {
            menuList();
        } else
            std::cout << "Invalid choice...\n";
    } while (value != 8);
}

User *UserManager::addUser(const std::string &user_name, const std::string &full_name, const std::string &password,
                           const std::string &email, bool allow_anonymous) {
    User *user = new User(next_id, user_name, full_name, password, email, allow_anonymous);
    users_by_id[user->getUserId()] = user;
    users_by_name[user->getUserName()] = user;
    next_id++;
    number_of_users++;
    return user;
}

User *UserManager::getUserById(int user_id) const {
    if (users_by_id.count(user_id)) {
        return users_by_id.find(user_id)->second;
    }
    return nullptr;
}

User *UserManager::getUserByUserName(const std::string &user_name) const {
    if (users_by_name.count(user_name)) {
        return users_by_name.find(user_name)->second;
    }
    return nullptr;
}

void UserManager::listSystemUsers() const {
    for (auto &[user_name, user]: users_by_name)
        user->print();
}
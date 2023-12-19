//
// Created by ahmed on 17/12/2023.
//

#include "AskMeSystem.h"

void AskMeSystem::run()  {
    Manager.loadData();

    mainMenu();

    Manager.saveData();
}

void AskMeSystem::mainMenu()  {
    int choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "\t1: Login\n";
        std::cout << "\t2: Sign UP\n";
        std::cout << "\t3: Exit\n";

        std::cout << "\nEnter number in range 1 - 3: ";
        std::cin >> choice;

        if (choice == 1)
            Manager.logIn();//Tell manager to login user
        else if (choice == 2)
            Manager.signUp();//Tell manager to sign up new user
        else if (choice != 3)
            std::cout << "Invalid choice.\n";
    } while (choice != 3);
}

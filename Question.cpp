//
// Created by ahmed on 17/12/2023.
//

#include "Question.h"

Question::Question(int id, int parent, int from, int to, const std::string &question, const std::string &answer,
                   bool anonymous)
        : id(id), parent_id(parent), from_user_id(from), to_user_id(to),
          question(question), answer(answer), anonymous(anonymous) {

}

void Question::print() const {
    if (getParentId() != getId())
        std::cout << "\tThread: ";

    std::cout << "Question id (" << getId() << ")";
    if (!getAnonymous())
        std::cout << " from user id(" << getFromUserId() << ")";
    std::cout << "\tQuestion: " << getQuestion() << "\n";

    if (hasAnswer()) {
        if (getParentId() != getId())
            std::cout << "\tThread: ";
        std::cout << "\tAnswer: " << getAnswer() << "\n";
    }
    std::cout << "\n";
}

void Question::printFromUser() const {
    std::cout << "Question id (" << getId() << ") ";
    if (getAnonymous())
        std::cout << "AQ ";
    std::cout << "to user id (" << getToUserId() << ") ";
    std::cout << "\tQuestion " << getQuestion() << "\n";

    if (hasAnswer())
        std::cout << "\tNot Answered yet.";
    else
        std::cout << "\tAnswer: " << getAnswer() << "\n";
}

void Question::printFeed() const {
    if (getParentId() != getId())
        std::cout << "Thread parent question id (" << getParentId() << ") , ";

    std::cout << "Question id (" << getId() << ") ";

    if (!getAnonymous())
        std::cout << "from user id (" << getFromUserId() << ") ";
    std::cout << "to user id (" << getToUserId() << ") ";

    std::cout << "\t" << getQuestion() << "\n";

    if (hasAnswer())
        std::cout << "\tNot Answered yet.";
    else
        std::cout << "\tAnswer: " << getAnswer() << "\n\n";
}

bool Question::hasAnswer() const {
    return !getAnswer().empty();
}

bool Question::getAnonymous() const {
    return anonymous;
}

int Question::getId() const {
    return id;
}

int Question::getParentId() const {
    return parent_id;
}

int Question::getFromUserId() const {
    return from_user_id;
}

int Question::getToUserId() const {
    return to_user_id;
}

const std::string &Question::getQuestion() const {
    return question;
}

const std::string &Question::getAnswer() const {
    return answer;
}

void Question::setAnswer(const std::string &answer_text) {
    answer = answer_text;
}
//
// Created by ahmed on 17/12/2023.
//

#include "QuestionManager.h"

QuestionManager::QuestionManager() {
    number_of_questions = next_id = 0;
}

QuestionManager::~QuestionManager() {
    questions_ids_by_parent.clear();
    for (auto &[id, question]: questions_by_id) {
        delete question;
        question = nullptr;
    }
    questions_by_id.clear();
}

void QuestionManager::loadData() {
    std::ifstream question_file("QuestionData.txt");
    if (!question_file.is_open()) {
        std::cout << "Error: Can't open file named 'QuestionData.txt'\n";
        return;
    }
    int id, parent_id, from_user_id, to_user_id;
    std::string question_text, answer;
    bool anonymous;

    question_file >> number_of_questions >> next_id;
    for (int i = 0; i < number_of_questions; ++i) {

        question_file >> id >> parent_id >> from_user_id >> to_user_id
                      >> question_text >> answer >> anonymous;

        Question *new_question = new Question(id, parent_id, from_user_id,
                                              to_user_id, question_text, answer, anonymous);

        questions_by_id[id] = new_question;
        questions_ids_by_parent[parent_id].insert(id);
    }
}

void QuestionManager::saveData() {
    std::ofstream question_file("QuestionData.txt");
    if (!question_file.is_open()) {
        std::cout << "Error: Can't open file named 'QuestionData.txt'\n";
        return;
    }
    question_file << number_of_questions << " " << next_id << "\n";
    for (auto [id, question]: questions_by_id) {
        question_file << question->getId() << " " << question->getParentId() << " "
                      << question->getFromUserId() << " " << question->getToUserId() << " "
                      << question->getQuestion() << " " << question->getAnswer() << " "
                      << question->getAnonymous() << "\n";
    }
}

void QuestionManager::printQuestionsToMe(int user_id) const {
    for (auto &[parent, questions_ids]: questions_ids_by_parent) {
        //skip questions not asked to me
        if (getQuestionById(parent)->getToUserId() != user_id)
            continue;

        for (auto &id: questions_ids) {
            if (getQuestionById(id) != nullptr) {
                getQuestionById(id)->print();
            } else {
                std::cout << "System Error: can't find question with ID (" << id << ").\n";
            }
        }
    }
}

void QuestionManager::printQuestionsFromMe(int user_id) const {
    for (auto &[question_id, question]: questions_by_id) {
        if (question->getFromUserId() == user_id) {
            question->printFromUser();
        }
    }
}

void QuestionManager::askQuestion(int from, int to, bool allow_anonymous) {
    std::string question_text;
    int parent;
    if (allow_anonymous) {
        int val;
        std::cout << "Do you wanna ask in anonymous mode (0 for no, otherwise for yes): ";
        std::cin >> val;
        allow_anonymous = val;
    } else {
        std::cout << "Anonymous questions are not allowed for this user.\n";
    }
    parent = inputQuestionId(true);

    std::cout << "Enter question text: ";
    std::cin.ignore();
    getline(std::cin, question_text);

    addNewQuestion(parent, from, to, question_text, allow_anonymous);
}

void QuestionManager::answerQuestion(int to) const {
    int question_id = inputQuestionId(false);

    //operation canceled
    if (question_id == -1)
        return;

    Question *question = getQuestionById(question_id);

    question->printFromUser();

    if (question->getToUserId() != to) {
        std::cout << "Not allowed to answer this question.\n";
    } else if (question->hasAnswer())
        std::cout << "Note: This question has been already answered.\n";
    std::cout << "Enter your answer: ";
    std::string answer_text;
    std::cin.ignore();
    std::getline(std::cin, answer_text);
    question->setAnswer(answer_text);
}

void QuestionManager::deleteQuestion(int from) {

    int question_id = inputQuestionId(false);
    if (question_id == -1)//this operation is cancelled
        return;

    Question *question = getQuestionById(question_id);

    //user can only delete questions that he asked
    if (question->getFromUserId() == from) {
        std::cout << "You aren\'t allowed to delete this question.\n";
        return;
    }

    if (question->getId() == question->getParentId()) {
        std::unordered_set<int> &ids =
                questions_ids_by_parent[question_id];
        questions_ids_by_parent.erase(question_id);
        for (auto id: ids) {
            Question *ptr = getQuestionById(id);

            if (ptr == nullptr)continue;

            questions_by_id.erase(question_id);
            delete ptr;
            ptr = nullptr;

            number_of_questions--;
        }
    } else {
        questions_ids_by_parent[question->getParentId()].
                erase(question_id);

        questions_by_id.erase(question_id);
        delete question;
        question = nullptr;

        number_of_questions--;
    }
}

void QuestionManager::feed() const {
    for (auto &[id, question]: questions_by_id)
        question->printFeed();
}

bool QuestionManager::checkQuestionId(int question_id) const {
    return getQuestionById(question_id) != nullptr;
}

int QuestionManager::inputQuestionId(bool thread) const {
    int question_id;

    if (thread)
        std::cout << "For thread question: Enter question id or -1 for new question: ";
    else
        std::cout << "Enter Question id or -1 to cancel: ";

    std::cin >> question_id;

    if (question_id == -1)//means cancel or new question
        return -1;

    if (!checkQuestionId(question_id)) {//not valid question id
        question_id = -1;

        std::cout << "Invalid question id.\n";

        if (thread)
            std::cout << "We will add new questions.\n";
    }

    return question_id;
}

Question *QuestionManager::getQuestionById(int question_id) const {
    if (questions_by_id.count(question_id))
        return questions_by_id.find(question_id)->second;
    return nullptr;
}

void QuestionManager::addNewQuestion(int parent, int from, int to, const std::string &question_text,
                                     bool allow_anonymous) {
    if (parent == -1)
        parent = next_id;

    Question *new_question = new Question(next_id, parent, from, to,
                                          question_text, "", allow_anonymous);
    questions_by_id[next_id] = new_question;
    questions_ids_by_parent[parent].insert(next_id);
    number_of_questions++;
    next_id++;
}
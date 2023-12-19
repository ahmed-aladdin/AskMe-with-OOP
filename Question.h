//
// Created by ahmed on 17/12/2023.
//
#include <iostream>

#ifndef ASKME_USING_C__OPP_QUESTION_H
#define ASKME_USING_C__OPP_QUESTION_H

class Question {
private:
    int id, parent_id, from_user_id, to_user_id;
    std::string question, answer;
    bool anonymous;
public:
    Question(int id, int parent, int from, int to,
             const std::string &question, const std::string &answer, bool anonymous);

    void print() const;

    void printFromUser() const;

    void printFeed() const;

    bool hasAnswer() const;

    bool getAnonymous() const;

    int getId() const;

    int getParentId() const;

    int getFromUserId() const;

    int getToUserId() const;

    const std::string &getQuestion() const;

    const std::string &getAnswer() const;

    void setAnswer(const std::string &answer_text);
};


#endif //ASKME_USING_C__OPP_QUESTION_H

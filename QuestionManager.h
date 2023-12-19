//
// Created by ahmed on 17/12/2023.
//
#include "Question.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef ASKME_USING_C__OPP_QUESTIONMANAGER_H
#define ASKME_USING_C__OPP_QUESTIONMANAGER_H

class QuestionManager {
private:
    int number_of_questions, next_id;
    std::unordered_map<int, Question *> questions_by_id;
    std::unordered_map<int, std::unordered_set<int>> questions_ids_by_parent;
public:
    QuestionManager();
    ~QuestionManager();
    void loadData();

    void saveData();

    void printQuestionsToMe(int user_id) const;

    void printQuestionsFromMe(int user_id) const;

    void askQuestion(int from, int to, bool allow_anonymous);

    void answerQuestion(int to)const;

    void deleteQuestion(int question_id);

    void feed() const;

    bool checkQuestionId(int question_id) const;

    int inputQuestionId(bool thread) const;

    Question *getQuestionById(int question_id) const;

    void addNewQuestion(int parent, int from, int to,
                        const std::string &question_text, bool allow_anonymous);
};


#endif //ASKME_USING_C__OPP_QUESTIONMANAGER_H

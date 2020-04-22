#pragma once
#include "includes.h"

class RegularExpression {

public:
    RegularExpression();
    RegularExpression(string);
    ~RegularExpression();

    void setPostfixExpression(string postfixExpression) {
        this->postfixExpression = postfixExpression;
    }

    string getPostfixExpression() {
        if (postfixExpression == "") convertInfixToPostfix();
        return postfixExpression;
    }

    void setExpression(string expression) {
        this->expression = expression;
    }

    string getExpression() {
        return expression;
    }

    void setExpressionType(string expressionType) {
        this->expressionType = expressionType;
    }

    string getExpressionType() {
        return this->expressionType;
    }


private:
    string expression, postfixExpression, expressionType;
    int getPrecedence(char);
    bool isOperator(char);
    void convertInfixToPostfix();
};

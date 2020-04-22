#include "../include/RegularExpression.h"

RegularExpression::RegularExpression() {
    postfixExpression = "";
}

RegularExpression::RegularExpression(string regularExpression) {
    postfixExpression = "";
    this->expression = regularExpression;
}

RegularExpression::~RegularExpression() {

}

void RegularExpression::convertInfixToPostfix() {
    stack<char> st;
    for (int i = 0; i < (int) expression.length(); i++) {
        if (expression[i] == '\\') {
            postfixExpression += expression[i++];
            postfixExpression += expression[i];
        }
        else if (expression[i] == '(') {
            st.push('(');
        } else if (expression[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                postfixExpression += st.top();
                st.pop();
            }
            st.pop();
        } else if (isOperator(expression[i])) {
            while (!st.empty() && st.top() != '(' && getPrecedence(st.top()) >= getPrecedence(expression[i])) {
                postfixExpression += st.top();
                st.pop();
            }
            st.push(expression[i]);
        } else {
            postfixExpression += expression[i];
        }
    }
    while (!st.empty()) {
        postfixExpression += st.top();
        st.pop();
    }
}

int RegularExpression::getPrecedence(char op) {
    if (op == '*') {
        return 3;
    }
    if (op == '~') {
        return 2;
    }
    if (op == '|') {
        return 1;
    }
    return 0;
}

bool RegularExpression::isOperator(char symbol) {
    return symbol == '*' || symbol == '|' || symbol == '~';
}

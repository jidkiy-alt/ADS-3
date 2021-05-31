// Copyright 2021 NNTU-CS
#include <string>

#include <iostream>

#include "tstack.h"

int priority(char ch) {
  switch (ch) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
      return 3;
    default:
      return -1;
  }
}

std::string infx2pstfx(std::string inf) {
    TStack < char > stack1;
    std::string temp, result;

    for (auto & i : inf) {
        if (i >= '0' && i <= '9') {
            temp = i;
            result += temp + " ";
        } else if (i == '(') {
            stack1.push(i);
        } else if (i == ')') {
            char top = stack1.get();
            stack1.pop();
            while (top != '(') {
                temp = top;
                result += temp + " ";
                top = stack1.get();
                stack1.pop();
            }
        } else {
            while (!stack1.isEmpty() && priority(stack1.get()) >= priority(i)) {
                temp = stack1.get();
                result += temp + " ";
                stack1.pop();
            }
            stack1.push(i);
        }
    }

    while (!stack1.isEmpty()) {
        temp = stack1.get();
        result += temp + " ";
        stack1.pop();
    }

    result.erase(result.end() - 1, result.end());
    return result;
}

int eval(std::string pst) {
    TStack < int > stack2;

    for (char i : pst) {
        if (i >= '0' && i <= '9') {
            stack2.push(i - '0');
        } else if (i != ' ') {
            int y = stack2.get();
            stack2.pop();
            int x = stack2.get();
            stack2.pop();
            switch (i) {
                case '*':
                    stack2.push(x * y);
                    break;
                case '/':
                    stack2.push(x / y);
                    break;
                case '+':
                    stack2.push(x + y);
                    break;
                case '-':
                    stack2.push(x - y);
                    break;
            }
        }
    }
    return stack2.get();
}

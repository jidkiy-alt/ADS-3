// Copyright 2021 NNTU-CS
#include <string>
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
  TStack<char> stack1;
  std::string  outStr;
  for (int i = 0; i < inf.size(); i++) {
    if ('0' <= inf[i] && inf[i] <= '9') {
      outStr += inf[i];
      if (inf[i+1] < '0' || inf[i+1] > '9')
        outStr += " ";
    } else {
      if ((stack1.isEmpty() || priority(inf[i]) == 0 ||
           priority(inf[i]) > priority(stack1.get())) &&
          priority(inf[i]) != 1) {
        stack1.push(inf[i]);
      } else if (priority(inf[i]) != 1 &&
                 priority(inf[i]) <= priority(stack1.get())) {
        while (priority(inf[i]) <= priority(stack1.get()) &&
               priority(stack1.get()) > 0) {
          outStr += stack1.get();
          outStr += " ";
          stack1.pop();
        }
        stack1.push(inf[i]);
      } else if (priority(inf[i]) == 1) {
        while (priority(stack1.get()) > 0) {
          outStr += stack1.get();
          outStr += " ";
          stack1.pop();
        }
        stack1.pop();
      }
    }
  }
  while (!stack1.isEmpty()) {
    outStr += stack1.get();
    outStr += " ";
    stack1.pop();
  }
  return outStr;
}
int calculate(char *op, int num1, int num2) {
  switch (*op) {
    case '+':
      return num1 + num2;
    case '-':
      return num1-num2;
    case '*':
      return num1 * num2;
    case '/':
      return num1 / num2;
  }
}

int eval(std::string pst) {
  TStack<int> stack2;
  for (int i = 0; i < pst.size(); i++) {
    if ('0' <= pst[i] && pst[i] <= '9') {
      stack2.push(pst[i] - '0');
    } else if (priority(pst[i]) == 2 || priority(pst[i]) == 3) {
      int num1 = stack2.get();
      stack2.pop();
      int num2 = stack2.get();
      stack2.pop();
      stack2.push(calculate(&pst[i], num1, num2));
    }
  }
  return stack2.get();
}

// rpn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <cmath>
#include <optional>

typedef double(*pfunc)(double);
std::map<std::string, pfunc> functionMap;

void initFuncMap()
{
  functionMap["cos"] = cos;
  functionMap["sin"] = sin;
  functionMap["tan"] = tan;
  functionMap["abs"] = fabs;
}

bool isOperator(const std::string& str)
{
  return (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/');
}

std::pair<bool,pfunc> isUnaryFunction(const std::string& str)
{
  auto it = functionMap.find(str);
  if (it != functionMap.end())
  {
    std::pair<bool, pfunc> ret;
    ret.first = true;
    ret.second = it->second;
    return std::make_pair(true, it->second);
  }
  else
  {
    return std::make_pair(false, nullptr);
  }
}

int main(int argc,char* argv[])
{
  std::stack<double> st;
  double op1, op2;
  initFuncMap();

  try
  {
    while (--argc)
    {
      ++argv;
      std::string arg(*argv);
      if (isOperator(arg))
      {
        switch (arg[0])
        {
        case '+':
          op2 = st.top();
          st.pop();
          op1 = st.top();
          st.pop();
          st.push(op1 + op2);
          break;
        case '-':
          op2 = st.top();
          st.pop();
          op1 = st.top();
          st.pop();
          st.push(op1 - op2);
          break;
        case '*':
          op2 = st.top();
          st.pop();
          op1 = st.top();
          st.pop();
          st.push(op1 * op2);
          break;
        case '/':
          op2 = st.top();
          st.pop();
          op1 = st.top();
          st.pop();
          st.push(op1 / op2);
          break;
        }
      }
      else if (auto[exists, p] = isUnaryFunction(arg); exists)
      {
        op1 = st.top();
        st.pop();
        st.push(p(op1));
      }
      else
      {
        st.push(std::stod(arg));
      }
    }

    std::cout << st.top() << "\n";
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
  }
}

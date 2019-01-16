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

class RPNCalc
{
public:
  typedef double(*pfunc)(double);

  RPNCalc()
  {
    initFuncMap();
  }
  ~RPNCalc() = default;

  bool isOperator(const std::string& str)
  {
    return (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/');
  }

  //if (auto[exists, p] = rpn.isUnaryFunction(arg); exists) // if function exists, use pointer returned.
  std::pair<bool, pfunc> isUnaryFunction2(const std::string& str)
  {
    auto it = functionMap_.find(str);
    if (it != functionMap_.end())
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

  // more elegant way to see if function exists and return function pointer if it does.
  std::optional<pfunc> isUnaryFunction(const std::string& str)
  {
    auto it = functionMap_.find(str);
    if (it != functionMap_.end())
    {
      std::pair<bool, pfunc> ret;
      ret.first = true;
      ret.second = it->second;
      return std::optional<pfunc>(it->second);
    }
    else
    {
      return std::nullopt;
    }
  }

  void plus()
  {
    auto op2 = st_.top();
    st_.pop();
    auto op1 = st_.top();
    st_.pop();
    st_.push(op1 + op2);
  }

  void minus()
  {
    auto op2 = st_.top();
    st_.pop();
    auto op1 = st_.top();
    st_.pop();
    st_.push(op1 - op2);
  }

  void multiplication()
  {
    auto op2 = st_.top();
    st_.pop();
    auto op1 = st_.top();
    st_.pop();
    st_.push(op1 * op2);
  }

  void division()
  {
    auto op2 = st_.top();
    st_.pop();
    auto op1 = st_.top();
    st_.pop();
    st_.push(op1 / op2);
  }

  void push(double value)
  {
    st_.push(value);
  }

  double pop()
  {
    auto op = st_.top();
    st_.pop();
    return op;
  }

  double top()
  {
    return st_.top();
  }

private:
  void initFuncMap()
  {
    functionMap_["acos"] = acos;
    functionMap_["cos"] = cos;
    functionMap_["asin"] = asin;
    functionMap_["sin"] = sin;
    functionMap_["atan"] = atan;
    functionMap_["tan"] = tan;
    functionMap_["abs"] = fabs;
    functionMap_["sqrt"] = sqrt;
    functionMap_["trunc"] = trunc;
  }

  std::map<std::string, pfunc> functionMap_;
  std::stack<double> st_;
};


int main(int argc,char* argv[])
{
  RPNCalc rpn;
  
  try
  {
    while (--argc)
    {
      ++argv;
      std::string arg(*argv);
      if (rpn.isOperator(arg))
      {
        switch (arg[0])
        {
        case '+':
          rpn.plus();
          break;
        case '-':
          rpn.minus();
          break;
        case '*':
          rpn.multiplication();
          break;
        case '/':
          rpn.division();
          break;
        }
      }
      else if (auto p = rpn.isUnaryFunction(arg))
      {
        auto op1 = rpn.pop();
        rpn.push(p.value()(op1));
      }
      else
      {
        rpn.push(std::stod(arg));
      }
    }

    std::cout << rpn.top() << "\n";
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
  }
}

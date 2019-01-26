// rpn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#include "RPNCalculator.h"

int main(int argc,char* argv[])
{
  RPNCalculator rpn;
  
  if (argc==1)
  {
    std::cerr << "Reverse Polish Notation Calculator v1.0 - Anders Karlsson\n";
    std::cout << rpn.show() << std::endl;
    return -1;
  }
  
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
        case '%':
          rpn.modal();
          break;
        }
      }
      else if (auto p = rpn.isUnaryFunction(arg))
      {
        auto op1 = rpn.pop();
        rpn.push(p.value()(op1));
      }
      else if (auto p = rpn.isFunction(arg))
      {
        auto op1 = rpn.pop();
        auto op2 = rpn.pop();
        rpn.push(p.value()(op2, op1));
      }
      else if (auto p = rpn.isSFunction(arg))
      {
        auto f = p.value();
        (rpn.*f)();
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
  
  return 0;
}

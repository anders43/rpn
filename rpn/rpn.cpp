// rpn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#include "RPNCalculator.h"

int main(int argc, char* argv[]) noexcept
{
  try
  {
    RPNCalculator rpn;

    if (argc == 1)
    {
      fmt::print("Reverse Polish Notation Calculator {} - Anders Karlsson 2020-10-20\n", 
        fmt::format(fg(fmt::color::yellow),"v1.1"));
      std::cout << rpn.show() << std::endl;
      return -1;
    }

    try
    {
      while (--argc)
      {
        ++argv;
        std::string arg(*argv);
        if (rpn.isOperand(arg))
        {
          continue;
        }
        else if (auto p1 = rpn.isUnaryFunction(arg))
        {
          const auto op1 = rpn.pop();
          rpn.push(p1.value()(op1));
        }
        else if (auto p2 = rpn.isFunction(arg))
        {
          const auto op1 = rpn.pop();
          const auto op2 = rpn.pop();
          rpn.push(p2.value()(op2, op1));
        }
        else if (auto p3 = rpn.isSFunction(arg))
        {
          const auto f = p3.value();
          (rpn.*f)();
        }
        else
        {
          fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold | fmt::emphasis::italic,
            "Invalid argument\n");
        }
      }

      fmt::print(fmt::fg(fmt::color::green), "{}\n", rpn.top());
    }
    catch (const std::exception& ex)
    {
      fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold | fmt::emphasis::italic, "{}\n", ex.what());
    }
  }
  catch (const std::exception& ex)
  {
    fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold | fmt::emphasis::italic, "{}\n", ex.what());
  }
  return 0;
}

#include "pch.h"
#include <cmath>
#include "RPNCalculator.h"


RPNCalculator::RPNCalculator()
{
  initFuncMap();
  initFunc2Map();
  initSFuncMap();
}


bool RPNCalculator::isOperator(const std::string_view str)
{
  // unary + -
  if ((str[0] == '+' || str[0] == '-') && str.length()>1)
  {
    return false;
  }
  
  return (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '%');
}

std::pair<bool, RPNCalculator::pfunc> RPNCalculator::isUnaryFunction2(const std::string& str)
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

std::optional<RPNCalculator::pfunc> RPNCalculator::isUnaryFunction(const std::string& str)
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

std::optional<RPNCalculator::p2func> RPNCalculator::isFunction(const std::string& str)
{
  auto it = function2Map_.find(str);
  if (it != function2Map_.end())
  {
    std::pair<bool, p2func> ret;
    ret.first = true;
    ret.second = it->second;
    return std::optional<p2func>(it->second);
  }
  else
  {
    return std::nullopt;
  }
}

std::optional < RPNCalculator::spfunc > RPNCalculator::isSFunction(const std::string& str)
{
  auto it = sfunctionMap_.find(str);
  if (it != sfunctionMap_.end())
  {
    std::pair<bool, spfunc> ret;
    ret.first = true;
    ret.second = it->second;
    return std::optional<spfunc>(it->second);
  }
  else
  {
    return std::nullopt;
  }
}

void RPNCalculator::plus()
{
  auto op2 = st_.top();
  st_.pop();
  auto op1 = st_.top();
  st_.pop();
  st_.push(op1 + op2);
}

void RPNCalculator::minus()
{
  auto op2 = st_.top();
  st_.pop();
  auto op1 = st_.top();
  st_.pop();
  st_.push(op1 - op2);
}

void RPNCalculator::multiplication()
{
  auto op2 = st_.top();
  st_.pop();
  auto op1 = st_.top();
  st_.pop();
  st_.push(op1 * op2);
}

void RPNCalculator::division()
{
  auto op2 = st_.top();
  st_.pop();
  auto op1 = st_.top();
  st_.pop();
  st_.push(op1 / op2);
}

void RPNCalculator::modal()
{
  auto op2 = st_.top();
  st_.pop();
  auto op1 = st_.top();
  st_.pop();
  st_.push(static_cast<double>(static_cast<int>(op1) % static_cast<int>(op2)));
}

void RPNCalculator::push(double value)
{
  st_.push(value);
}

double RPNCalculator::pop()
{
  auto op = st_.top();
  st_.pop();
  return op;
}

double RPNCalculator::top()
{
  return st_.top();
}

double fak(double value)
{
  double s{ 1.0 };
  double i = 2.0;
  while (i <= value)
  {
    s *= i;
    i += 1.0;
  }
  return s;
}

void RPNCalculator::lsh()
{
  auto n = static_cast<int>(st_.top());
  st_.pop();
  auto op = static_cast<uint32_t>(st_.top());
  op <<= n;
  st_.push(static_cast<double>(op));
}

void RPNCalculator::rsh()
{
  auto n = static_cast<int>(st_.top());
  st_.pop();
  auto op = static_cast<uint32_t>(st_.top());
  op >>= n;
  st_.push(static_cast<double>(op));
}

void RPNCalculator::initFuncMap()
{
  functionMap_["acos"] = acos;
  functionMap_["cos"] = cos;
  functionMap_["asin"] = asin;
  functionMap_["sin"] = sin;
  functionMap_["atan"] = atan;
  functionMap_["tan"] = tan;
  functionMap_["fabs"] = fabs;
  functionMap_["sqrt"] = sqrt;
  functionMap_["trunc"] = trunc;
  functionMap_["floor"] = floor;
  functionMap_["exp"] = exp;
  functionMap_["log"] = log;
  functionMap_["log10"] = log10;
  functionMap_["round"] = round;
  functionMap_["!"] = fak;
}

void RPNCalculator::initFunc2Map()
{
  function2Map_["fmod"] = fmod;
  function2Map_["fmax"] = fmax;
  function2Map_["fmin"] = fmin;
  function2Map_["pow"] = pow;
  function2Map_["^"] = pow;
  function2Map_["remainder"] = remainder;
}

void RPNCalculator::initSFuncMap()
{
  sfunctionMap_["lsh"] = &RPNCalculator::lsh;
  sfunctionMap_["rsh"] = &RPNCalculator::rsh;
}

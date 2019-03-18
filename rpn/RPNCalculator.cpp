#include "pch.h"
#include <cmath>
#include <string>
#include <sstream>
#include "RPNCalculator.h"

RPNCalculator::RPNCalculator() noexcept
{
  initFuncMap();
  initFunc2Map();
  initSFuncMap();
}

bool RPNCalculator::isOperand(const std::string& str)
{
  try
  {
    st_.push(std::stod(str));
  }
  catch (const std::exception&)
  {
    return false; // failed conversion
  }
  return true;
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

void RPNCalculator::addition()
{
  const auto op2 = pop();
  const auto op1 = pop();
  st_.push(op1 + op2);
}

void RPNCalculator::subtraction()
{
  const auto op2 = pop();
  const auto op1 = pop();
  st_.push(op1 - op2);
}

void RPNCalculator::multiplication()
{
  const auto op2 = pop();
  const auto op1 = pop();
  st_.push(op1 * op2);
}

void RPNCalculator::division()
{
  const auto op2 = pop();
  const auto op1 = pop();
  st_.push(op1 / op2);
}

void RPNCalculator::modal()
{
  const auto op2 = pop();
  const auto op1 = pop();
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

void RPNCalculator::fak() 
{
  const auto top = static_cast<long long>(pop());
  long long s{ 1 };
  long long i = 2;
  while (i <= top)
  {
    s *= i;
    i += 1;
  }
  push(static_cast<double>(s));
}

void RPNCalculator::lsh()
{
  const auto n = static_cast<int>(pop());
  auto op = static_cast<uint32_t>(pop());
  op <<= n;
  st_.push(static_cast<double>(op));
}

void RPNCalculator::rsh()
{
  const auto n = static_cast<int>(pop());
  auto op = static_cast<uint32_t>(pop());
  op >>= n;
  st_.push(static_cast<double>(op));
}

void RPNCalculator::dup()
{
  auto op = st_.top();
  st_.push(op);
}

void RPNCalculator::rot()
{
  const auto op1 = pop();
  const auto op2 = pop();
  st_.push(op1);
  st_.push(op2);
}

void RPNCalculator::drop()
{
  st_.pop();
}

std::string RPNCalculator::show()
{
  std::stringstream ss;
  for (auto&& [f, p] : functionMap_)
    ss << f << " ";
  for (auto&& [f, p] : function2Map_)
    ss << f << " ";
  for (auto&& [f, p] : sfunctionMap_)
    ss << f << " ";
  return ss.str();
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
  sfunctionMap_["dup"] = &RPNCalculator::dup;
  sfunctionMap_["drop"] = &RPNCalculator::drop;
  sfunctionMap_["rot"] = &RPNCalculator::rot;
  sfunctionMap_["+"] = &RPNCalculator::addition;
  sfunctionMap_["-"] = &RPNCalculator::subtraction;
  sfunctionMap_["*"] = &RPNCalculator::multiplication;
  sfunctionMap_["/"] = &RPNCalculator::division;
  sfunctionMap_["%"] = &RPNCalculator::modal;
  sfunctionMap_["!"] = &RPNCalculator::fak;
}

#pragma once
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <optional>

class RPNCalculator
{
public:
  RPNCalculator();
  ~RPNCalculator() = default;;

public:
  typedef double(*pfunc)(double);
  typedef double(*p2func)(double, double);

  bool isOperator(const std::string_view str);

  //if (auto[exists, p] = rpn.isUnaryFunction(arg); exists) // if function exists, use pointer returned.
  std::pair<bool, pfunc> isUnaryFunction2(const std::string& str);
  std::optional<pfunc> isUnaryFunction(const std::string& str);
  std::optional<p2func> isFunction(const std::string& str);

  void plus();
  void minus();
  void multiplication();
  void division();
  void modal();
  void push(double value);
  double pop();
  double top();

private:
  void initFuncMap();
  void initFunc2Map();

  std::map<std::string, pfunc> functionMap_;
  std::map<std::string, p2func> function2Map_;
  std::stack<double> st_;

};


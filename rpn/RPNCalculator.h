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
  typedef void(RPNCalculator::*spfunc)(void);

  bool isOperator(const std::string_view str);

  std::pair<bool, pfunc> isUnaryFunction2(const std::string& str);
  std::optional<pfunc> isUnaryFunction(const std::string& str);
  std::optional<p2func> isFunction(const std::string& str);
  std::optional<spfunc> isSFunction(const std::string& str);

  void plus();
  void minus();
  void multiplication();
  void division();
  void modal();
  void push(double value);
  double pop();
  double top();
  void lsh();
  void rsh();
private:
  void initFuncMap();
  void initFunc2Map();
  void initSFuncMap();

  std::map<std::string, pfunc> functionMap_;
  std::map<std::string, p2func> function2Map_;
  std::map<std::string, spfunc> sfunctionMap_;
  std::stack<double> st_;
  bool init_{ false };
};

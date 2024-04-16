#ifndef SMART_CALC_2_SRC_MODEL_MODEL_CALCULATOR_H_
#define SMART_CALC_2_SRC_MODEL_MODEL_CALCULATOR_H_

#include <cmath>
#include <cstring>
#include <functional>
#include <stack>
#include <string>

namespace  {
class Calculator {
 public:
  Calculator();
  ~Calculator();
  void SetX(double input_x);
  void SetExpression(std::string input_str);
  bool NoErrors();
  int GetErrorCode();
  double GetResult();

 private:
  std::string str_temp_;
  std::string str_expression_;
  std::string::iterator it_str_expression_;
  std::stack<char> char_stack_;
  std::stack<double> double_stack_;
  std::function<double(double, double)> functional_;
  double result_;
  double x_;

  enum Flags {
    OK,
    INCORRECT_STR,
    CALC_ERROR,
    INCORRECT_BINARY_OPERATOR,
    INCORRECT_UNARY_OPERATOR,
    INCORRECT_UNARY_MINUS,
    INCORRECT_NUMBER,
    INCORRECT_POINT,
    INCORRECT_X,
    INCORRECT_END,
    EMPTY_BRAKETS,
    INCORRECT_FUNCTIONAL
  };

  Flags flag_;

  const static size_t functions_arr_size =
      36;  // there are 36 Functions and Numbers

  struct Functions {
    char short_function;                               // 's'
    char long_function[8];                             // "sin"
    int long_function_size;                            // 3
    int function_priority;                             // 4
    std::function<double(double, double)> functional;  // Calculator::sin
  };

  struct Functions functions_arr[functions_arr_size] = {
      {'x', "x", 1, 0, sum},      {'(', "(", 1, 0, sum},
      {')', ")", 1, 0, sum},      {'.', ",", 1, 0, sum},
      {'0', "0", 1, 0, sum},      {'1', "1", 1, 0, sum},
      {'2', "2", 1, 0, sum},      {'3', "3", 1, 0, sum},
      {'4', "4", 1, 0, sum},      {'5', "5", 1, 0, sum},
      {'6', "6", 1, 0, sum},      {'7', "7", 1, 0, sum},
      {'8', "8", 1, 0, sum},      {'9', "9", 1, 0, sum},
      {'+', "+", 1, 1, sum},      {'-', "-", 1, 1, subtract},
      {'*', "*", 1, 2, multiply}, {'/', "/", 1, 2, divide},
      {'M', "mod", 3, 2, mod},    {'e', "exp", 3, 4, exp},
      {'q', "sqrt", 4, 4, sqrt},  {'l', "log", 3, 4, log},
      {'L', "ln", 2, 4, ln},      {'s', "sin", 3, 4, sin},
      {'c', "cos", 3, 4, cos},    {'t', "tan", 3, 4, tan},
      {'g', "cot", 3, 4, cot},    {'S', "asin", 4, 4, asin},
      {'C', "acos", 4, 4, acos},  {'T', "atan", 4, 4, atan},
      {'G', "acot", 4, 4, acot},  {'^', "^", 1, 3, pow},
      {'E', "e", 1, 0, sum},      {'E', "E", 1, 0, sum},
      {'.', ".", 1, 0, sum},      {'~', "~", 1, 5, change_sign}};

  int GetPriority(char temp);
  std::function<double(double, double)> GetFunctional(const std::string &token);

  // static binary functions for std::function<double(double, double)>
  static double sum(double a, double b) { return b + a; }
  static double subtract(double a, double b) { return b - a; }
  static double divide(double a, double b) { return b / a; }
  static double multiply(double a, double b) { return b * a; }
  static double mod(double a, double b) { return std::fmod(b, a); }
  static double pow(double a, double b) { return std::pow(b, a); }

  // static unary functions for std::function<double(double, double)>
  static double change_sign(double a, double b) {
    b = a;
    return b * (-1);
  }
  static double exp(double a, double b) {
    b = a;
    return std::exp(b);
  }
  static double sqrt(double a, double b) {
    b = a;
    return std::sqrt(b);
  }
  static double log(double a, double b) {
    b = a;
    return std::log10(b);
  }
  static double ln(double a, double b) {
    b = a;
    return std::log(b);
  }
  static double sin(double a, double b) {
    b = a;
    return std::sin(b);
  }
  static double cos(double a, double b) {
    b = a;
    return std::cos(b);
  }
  static double tan(double a, double b) {
    b = a;
    return std::tan(b);
  }
  static double cot(double a, double b) {
    b = a;
    return 1.0 / std::tan(b);
  }
  static double asin(double a, double b) {
    b = a;
    return std::asin(b);
  }
  static double acos(double a, double b) {
    b = a;
    return std::acos(b);
  }
  static double atan(double a, double b) {
    b = a;
    return std::atan(b);
  }
  static double acot(double a, double b) {
    b = a;
    return 1.0 / std::atan(b);
  }

  void SimplifyExpression();
  void UnaryMinusAndScientificNotation();
  void CheckStrFirstCharacter();
  bool CheckPrevNext();
  void ScientificNotation();
  void CheckStrMiddle();
  void CheckStrEnd();
  bool CheckBinaryOperator();
  bool CheckUnaryOperator();
  bool CheckUnaryMinus();
  bool CheckNumber();
  bool CheckPoint();
  bool CheckX();
  bool CheckBrakets();
  bool CheckEnd();
  void CheckOperators();
  bool CheckNumberPoint();
  bool CheckOperator();
  void AddDelimiters();
  bool IsDigitsAndX(const std::string &token);
  void ToCharStack(const std::string &token);
  void ToRPN();
  bool IsDigits(const std::string &token);
  bool IsBinaryOperator(const std::string &token);
  bool IsUnaryOperator(const std::string &token);
  void ToDoubleStack(const std::string &token);
  double CalcRPN();
};
}  // namespace 
#endif  // SMART_CALC_2_SRC_MODEL_MODEL_CALCULATOR_H_

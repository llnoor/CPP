#include "model_calculator.h"

namespace  {
Calculator::Calculator() {
  str_expression_ = "";
  result_ = 0;
  x_ = 0;
  flag_ = OK;
}

Calculator::~Calculator() = default;

void Calculator::SetX(double input_x) { x_ = input_x; }

void Calculator::SetExpression(std::string input_str) {
  flag_ = OK;
  result_ = 0;
  str_expression_ = "";
  if (input_str.size() > 255)
    flag_ = INCORRECT_STR;
  else
    str_expression_ = '(' + input_str + ')';
  if (flag_ == OK) SimplifyExpression();
  if (flag_ == OK) UnaryMinusAndScientificNotation();
  if (flag_ == OK) CheckOperators();
  if (flag_ == OK) AddDelimiters();
  if (flag_ == OK) ToRPN();
}

bool Calculator::NoErrors() { return (flag_ == OK); }

int Calculator::GetErrorCode() { return flag_; }

double Calculator::GetResult() {
  if (flag_ == OK)
    CalcRPN();
  else
    result_ = 0.0 / 0.0;
  return result_;
}

void Calculator::SimplifyExpression() {
  int bracket = 0;
  bool not_invalid_characters = true;
  str_temp_ = "";
  it_str_expression_ = str_expression_.begin();
  while (it_str_expression_ != str_expression_.end() && flag_ == OK) {
    not_invalid_characters = true;
    for (size_t i = 0; i < functions_arr_size && not_invalid_characters; i++) {
      if (!strncmp(it_str_expression_.base(), functions_arr[i].long_function,
                   functions_arr[i].long_function_size)) {
        str_temp_ += functions_arr[i].short_function;
        it_str_expression_ += functions_arr[i].long_function_size;
        if (functions_arr[i].short_function == '(')
          bracket++;
        else if (functions_arr[i].short_function == ')')
          bracket--;
        not_invalid_characters = false;
      } else if (i == functions_arr_size - 1) {
        flag_ = INCORRECT_STR;
      }
    }
  }
  if (bracket != 0) flag_ = INCORRECT_STR;
  str_expression_ = str_temp_;
}

void Calculator::UnaryMinusAndScientificNotation() {
  str_temp_ = "";
  it_str_expression_ = str_expression_.begin();
  CheckStrFirstCharacter();
  CheckStrMiddle();
  CheckStrEnd();
  str_expression_ = str_temp_;
}

void Calculator::CheckStrFirstCharacter() {
  if (strchr("(0123456789x-+eqlLsctgSCTG", *it_str_expression_)) {
    str_temp_ += *it_str_expression_;
    it_str_expression_++;
  }
}

bool Calculator::CheckPrevNext() {
  return (strchr("(+-*M/^", *(it_str_expression_ - 1)) &&
          strchr("(0123456789x~eqlLsctgSCTG", *(it_str_expression_ + 1)));
}

void Calculator::ScientificNotation() {
  if (*(it_str_expression_ + 1) == '+') {
    str_temp_ += "*10^";
    it_str_expression_ += 2;
  } else if (*(it_str_expression_ + 1) == '-') {
    str_temp_ += "*10^~";
    it_str_expression_ += 2;
  } else {
    str_temp_ += "*10^";
    it_str_expression_++;
  }
}

void Calculator::CheckStrMiddle() {
  while ((it_str_expression_ + 1) != str_expression_.end() && flag_ == OK) {
    if (*it_str_expression_ == '-' && CheckPrevNext()) {
      str_temp_ += '~';
      it_str_expression_++;
    } else if (*it_str_expression_ == '+' && CheckPrevNext()) {
      it_str_expression_++;
    } else if (*it_str_expression_ == 'E') {
      ScientificNotation();
    } else {
      str_temp_ += *it_str_expression_;
      it_str_expression_++;
    }
  }
}

void Calculator::CheckStrEnd() {
  if ((it_str_expression_ + 1) == str_expression_.end() &&
      strchr(")0123456789x", *it_str_expression_)) {
    str_temp_ += *it_str_expression_;
  }
}

bool Calculator::CheckBinaryOperator() {
  return strchr("+-*M/^", *it_str_expression_) &&
         (!strchr(")0123456789x", *(it_str_expression_ - 1)) ||
          !strchr("(0123456789x~eqlLsctgSCTG", *(it_str_expression_ + 1)));
}

bool Calculator::CheckUnaryOperator() {
  return strchr("eqlLsctgSCTG", *it_str_expression_) &&
         (!strchr("()+-*M/^~", *(it_str_expression_ - 1)) ||
          !strchr("(", *(it_str_expression_ + 1)));
}

bool Calculator::CheckUnaryMinus() {
  return strchr("~", *it_str_expression_) &&
         (!strchr("(+-*M/^", *(it_str_expression_ - 1)) ||
          !strchr("(0123456789xeqlLsctgSCTG", *(it_str_expression_ + 1)));
}

bool Calculator::CheckNumber() {
  return strchr("0123456789", *it_str_expression_) &&
         (!strchr("0123456789.(+-*M/^~", *(it_str_expression_ - 1)) ||
          !strchr("0123456789.)+-*M/^", *(it_str_expression_ + 1)));
}

bool Calculator::CheckPoint() {
  return strchr(".", *it_str_expression_) &&
         (!strchr("0123456789", *(it_str_expression_ - 1)) ||
          !strchr("0123456789", *(it_str_expression_ + 1)));
}

bool Calculator::CheckX() {
  return strchr("x", *it_str_expression_) &&
         (!strchr("(+-*M/^~", *(it_str_expression_ - 1)) ||
          !strchr(")+-*M/^", *(it_str_expression_ + 1)));
}

bool Calculator::CheckBrakets() {
  return ((strchr("(", *(it_str_expression_ - 1)) &&
           strchr(")", *it_str_expression_)) ||
          (strchr("(", *it_str_expression_) &&
           strchr(")", *(it_str_expression_ + 1))));
}

bool Calculator::CheckEnd() {
  return !((it_str_expression_ + 1) == str_expression_.end() &&
           strchr(")0123456789x", *(it_str_expression_)));
}

void Calculator::CheckOperators() {
  // flag_ = OK;
  it_str_expression_ = str_expression_.begin();
  // it_str_expression_++; // del
  while ((it_str_expression_ + 1) != str_expression_.end() && flag_ == OK) {
    if (CheckBinaryOperator()) {
      flag_ = INCORRECT_BINARY_OPERATOR;
    } else if (CheckUnaryOperator()) {
      flag_ = INCORRECT_UNARY_OPERATOR;
    } else if (CheckUnaryMinus()) {
      flag_ = INCORRECT_UNARY_MINUS;
    } else if (CheckNumber()) {  // 6
      flag_ = INCORRECT_NUMBER;
    } else if (CheckPoint()) {
      flag_ = INCORRECT_POINT;
    } else if (CheckX()) {
      flag_ = INCORRECT_X;
    } else if (CheckBrakets()) {
      flag_ = EMPTY_BRAKETS;
    }
    it_str_expression_++;
  }

  if (CheckEnd()) {
    if (flag_ == OK) flag_ = INCORRECT_END;
  }
}

bool Calculator::CheckNumberPoint() {
  return strchr(".0123456789", *it_str_expression_);
}

bool Calculator::CheckOperator() {
  return strchr("()~x+-*M/^eqlLsctgSCTG", *it_str_expression_);
}

void Calculator::AddDelimiters() {
  str_temp_ = "";
  it_str_expression_ = str_expression_.begin();
  while (it_str_expression_ != str_expression_.end() && flag_ == OK) {
    if (CheckOperator()) {
      str_temp_ += *it_str_expression_;
      str_temp_ += ' ';
      it_str_expression_++;
    } else if (CheckNumberPoint()) {
      int point_count = 0;
      while (CheckNumberPoint()) {
        if (*it_str_expression_ == '.') point_count++;
        str_temp_ += *it_str_expression_;
        it_str_expression_++;
      }
      if (point_count > 1) flag_ = INCORRECT_STR;
      str_temp_ += ' ';
    }
  }
  str_temp_.pop_back();
  str_expression_ = str_temp_;
}

bool Calculator::IsDigitsAndX(const std::string &token) {
  return token.find_first_not_of(".0123456789x") == std::string::npos;
}

void Calculator::ToCharStack(const std::string &token) {
  std::string temp_temp_str = "";
  if (IsDigitsAndX(token)) {
    str_temp_ += token;
    str_temp_ += " ";
  } else if ('(' == token.at(0)) {
    char_stack_.push('(');
  } else if (')' == token.at(0)) {
    while (char_stack_.top() != '(') {
      str_temp_ += char_stack_.top();
      char_stack_.pop();
      str_temp_ += " ";
    }
    char_stack_.pop();  // to pop '(';
  } else {
    while (GetPriority(char_stack_.top()) >= GetPriority(token.at(0))) {
      if ((GetPriority(char_stack_.top()) == 3) &&
          (GetPriority(token.at(0)) == 3)) {
        break;  // exception for the pow function
      }
      str_temp_ += char_stack_.top();
      char_stack_.pop();
      str_temp_ += " ";
    }
    char_stack_.push(token.at(0));
  }
}

void Calculator::ToRPN() {
  str_temp_ = "";
  while (!char_stack_.empty()) char_stack_.pop();
  std::string token;
  while (token != str_expression_) {
    token = str_expression_.substr(0, str_expression_.find_first_of(" "));
    str_expression_ =
        str_expression_.substr(str_expression_.find_first_of(" ") + 1);
    ToCharStack(token);
  }
  while (!char_stack_.empty()) {
    if (char_stack_.top() != '(') str_temp_ += char_stack_.top();
    char_stack_.pop();
    str_temp_ += " ";
  }
  str_expression_ = str_temp_;
}

bool Calculator::IsDigits(const std::string &token) {
  return token.find_first_not_of(".0123456789") == std::string::npos;
}

bool Calculator::IsBinaryOperator(const std::string &token) {
  return token.find_first_not_of("+-*M/^") == std::string::npos;
}

bool Calculator::IsUnaryOperator(const std::string &token) {
  return token.find_first_not_of("~eqlLsctgSCTG") == std::string::npos;
}

void Calculator::ToDoubleStack(const std::string &token) {
  double arg1 = 0.0;
  double arg2 = 0.0;
  if (IsDigits(token)) {
    if (!token.empty()) {
      arg1 = std::stod(token);
      double_stack_.push(arg1);
    }
  } else if ('x' == token.at(0)) {
    double_stack_.push(x_);
  } else if (IsBinaryOperator(token)) {
    arg1 = double_stack_.top();
    double_stack_.pop();
    arg2 = double_stack_.top();
    double_stack_.pop();
    functional_ = GetFunctional(token);
    double_stack_.push(functional_(arg1, arg2));
  } else if (IsUnaryOperator(token)) {
    arg1 = double_stack_.top();
    double_stack_.pop();
    functional_ = GetFunctional(token);
    double_stack_.push(functional_(arg1, 0));
  }
}

double Calculator::CalcRPN() {
  str_temp_ = str_expression_;
  while (!double_stack_.empty()) double_stack_.pop();
  std::string token;

  while (token != str_expression_) {
    token = str_expression_.substr(0, str_expression_.find_first_of(" "));
    str_expression_ =
        str_expression_.substr(str_expression_.find_first_of(" ") + 1);
    ToDoubleStack(token);
  }
  result_ = double_stack_.top();
  double_stack_.pop();
  str_expression_ = str_temp_;
  return result_;
}

int Calculator::GetPriority(char temp) {
  int priority = -1;
  for (size_t i = 13; i < functions_arr_size; i++) {
    if (temp == functions_arr[i].short_function) {
      priority = functions_arr[i].function_priority;
      break;
    }
  }
  return priority;
}

std::function<double(double, double)> Calculator::GetFunctional(
    const std::string &token) {
  std::function<double(double, double)> temp_functional;
  for (size_t i = 13; i < functions_arr_size; i++) {
    if (token.at(0) == functions_arr[i].short_function) {
      temp_functional = functions_arr[i].functional;
      break;
    }
  }
  return temp_functional;
}
}  // namespace 

#include "calculate.h"

std::pair<bool, double> s21::Calculate::CalculateAnswer(std::string &input,
                                                        double x) {
  std::pair<bool, double> answer;
  answer.first = false;
  answer.second = 0.0;
  if (PolishNot(input, x) != -1) {
    if (CalculatePolishNotation()) {
      answer.first = true;
      answer.second = result_;
      output_.clear();
      result_ = 0;
    }
  }
  return answer;
}

bool s21::Calculate::CalculatePolishNotation() {
  bool calc_result = true;
  std::stack<double> calculated{};
  double right{};
  double left{};
  for (size_t i = 0; i < output_.size(); ++i) {
    if (output_[i].flag_ == kNumber) {
      calculated.push(output_[i].number_);
    } else if (output_[i].flag_ == kOperator && calculated.size() > 1) {
      right = calculated.top();
      calculated.pop();
      left = calculated.top();
      calculated.pop();
      calculated.push(CalcOperators(right, left, output_[i].operator_));
    } else if (output_[i].flag_ == kUnarMinus && !calculated.empty()) {
      calculated.top() *= -1;
    } else if (output_[i].flag_ == kFunction && !calculated.empty()) {
      calculated.top() = CalcFunctions(calculated.top(), output_[i].function_);
    } else {
      calc_result = false;
    }
  }
  if (calculated.size() == 1) {
    result_ = calculated.top();
  } else {
    calc_result = false;
  }
  return calc_result;
}

int s21::Calculate::PolishNot(std::string &input, double x) {
  int flag_stop = 0;
  size_t i = 0;
  std::string function_name{};
  std::stack<OutputString> temp{};
  while (i < input.length() && flag_stop == 0) {
    size_t idx{};
    if (isdigit(input[i])) {
      double number = std::stod(input.substr(i), &idx);
      i += idx;
      output_.push_back({
          kNumber,
          number,
          0,
          "",
      });
    } else if (input[i] == 'x') {
      i++;
      output_.push_back({
          kNumber,
          x,
          0,
          "",
      });
    } else if (isalpha(input[i]) && input[i] != 'x') {
      idx = i;
      while (isalpha(input[i])) i++;
      function_name = input.substr(idx, i - idx);
      temp.push({kFunction, 0.0, 0, function_name, kExpFuns});
    } else if (input[i] == '(') {
      temp.push({kOpenBrace, 0, 0, "", -1});
      i++;
    } else if (input[i] == '-' && IsUnarOperator(input, &i)) {
      temp.push({kUnarMinus, 0.0, '~', "", kExpFuns});
    } else if (IsOperator(input[i])) {
      FromStackToOutput(temp, output_, input[i], 0);
      temp.push({kOperator, 0.0, input[i], "", DefinePriority(input[i])});
      i++;
    } else if (input[i] == ')') {
      FromStackToOutput(temp, output_, 0, 1);
      if (!temp.empty() && temp.top().flag_ == kOpenBrace) {
        temp.pop();
      }
      if (!temp.empty() && temp.top().flag_ == kFunction) {
        output_.push_back(temp.top());
        temp.pop();
      }
      i++;
    } else
      flag_stop = -1;
  }
  if (!temp.empty() && temp.top().flag_ == kOpenBrace)
    flag_stop = -1;
  else {
    while (!temp.empty()) {
      output_.insert(output_.end(), temp.top());
      temp.pop();
    }
  }

  return flag_stop;
}

int s21::Calculate::DefinePriority(char operator_symbol) {
  int result{};
  switch (operator_symbol) {
    case '-':
    case '+':
      result = kSumSub;
      break;
    case '*':
    case '/':
    case '%':
      result = kDivMulMod;
      break;
    default:
      result = kExpFuns;
      break;
  }
  return result;
}

bool s21::Calculate::IsOperator(char operator_symbol) {
  return operator_symbol == '-' || operator_symbol == '+' ||
         operator_symbol == '*' || operator_symbol == '/' ||
         operator_symbol == '%' || operator_symbol == '^' ||
         operator_symbol == 'd';
}

bool s21::Calculate::IsUnarOperator(std::string &input, size_t *idx) {
  bool result = false;
  if (*idx == 0 || (*idx != 0 && input[*idx - 1] != ')' &&
                    input[*idx - 1] != 'x' && !isdigit(input[*idx - 1]))) {
    result = true;
    *idx += 1;
  }
  return result;
}

void s21::Calculate::FromStackToOutput(std::stack<OutputString> &stack_temp,
                                       std::vector<OutputString> &output,
                                       char operator_symbol, int flag) {
  if (flag == 0) {
    if (operator_symbol == '^') {
      while (!stack_temp.empty() &&
             stack_temp.top().priority_ > DefinePriority(operator_symbol)) {
        output.push_back(stack_temp.top());
        stack_temp.pop();
      }
    } else {
      while (!stack_temp.empty() &&
             stack_temp.top().priority_ >= DefinePriority(operator_symbol)) {
        output.push_back(stack_temp.top());
        stack_temp.pop();
      }
    }
  } else {
    while (!stack_temp.empty() && stack_temp.top().flag_ != kOpenBrace) {
      output.push_back(stack_temp.top());
      stack_temp.pop();
    }
  }
}

double s21::Calculate::CalcOperators(double right, double left,
                                     char operator_symbol) {
  double result{};
  switch (operator_symbol) {
    case '+':
      result = left + right;
      break;
    case '-':
      result = left - right;
      break;
    case '*':
      result = left * right;
      break;
    case '/':
      result = left / right;
      break;
    case '%':
      result = fmodl(left, right);
      break;
    case '^':
      result = powl(left, right);
      break;
  }
  return result;
}

double s21::Calculate::CalcFunctions(double number, std::string &function) {
  double result{};
  if (function == "sin") {
    result = sin(number);
  } else if (function == "cos") {
    result = cos(number);
  } else if (function == "tan") {
    result = tan(number);
  } else if (function == "sqrt") {
    result = sqrt(number);
  } else if (function == "asin") {
    result = asin(number);
  } else if (function == "atan") {
    result = atan(number);
  } else if (function == "acos") {
    result = acos(number);
  } else if (function == "ln") {
    result = log(number);
  } else if (function == "log") {
    result = log10(number);
  }
  return result;
}

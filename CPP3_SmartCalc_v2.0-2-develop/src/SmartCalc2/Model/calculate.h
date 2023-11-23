#ifndef CPP3_SMARTCALC_V2_MODEL_CALCULATE_H_
#define CPP3_SMARTCALC_V2_MODEL_CALCULATE_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

struct OutputString {
  char flag_{};
  double number_{};
  char operator_{};
  std::string function_{};
  int priority_{};
};

enum { kNumber = 0, kOpenBrace, kFunction, kOperator, kUnarMinus };
enum { kSumSub = 0, kDivMulMod, kExpFuns };

namespace s21 {
class Calculate {
 public:
  Calculate() {}
  ~Calculate() {}

  std::pair<bool, double> CalculateAnswer(std::string &input, double x);
  bool IsOperator(char operator_);

 private:
  int PolishNot(std::string &input, double x);
  int DefinePriority(char operator_symbol);

  bool CalculatePolishNotation();
  bool IsUnarOperator(std::string &input, size_t *idx);
  double CalcOperators(double right, double left_, char operator_symbol);
  double CalcFunctions(double number, std::string &function);
  void FromStackToOutput(std::stack<OutputString> &stack_temp,
                         std::vector<OutputString> &output,
                         char operator_symbol, int flag);
  std::vector<OutputString> output_{};
  double result_{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_CALCULATE_H_

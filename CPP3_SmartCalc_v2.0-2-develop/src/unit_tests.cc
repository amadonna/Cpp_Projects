#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "SmartCalc2/Model/calculate.h"

TEST(CalculateTest, SimpleExp_1) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string simple_ex = "1+2+3+4+5+6+8+9+10";
  answer = calc.CalculateAnswer(simple_ex, 0);
  ASSERT_TRUE(answer.second == 48.0 && answer.first);
}

TEST(CalculateTest, SimpleExp_2) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string simple_braces = "1-(10+15)";
  answer = calc.CalculateAnswer(simple_braces, 0);

  ASSERT_TRUE(answer.first && answer.second == -24.0);
}

TEST(CalculateTest, SimpleExp_3) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string simple_div = "1/3.4/97";
  answer = calc.CalculateAnswer(simple_div, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, (1 / 3.4 / 97));
}

TEST(CalculateTest, SimpleExp_4) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string exponentiation = "2^3^2";
  answer = calc.CalculateAnswer(exponentiation, 0);
  ASSERT_TRUE(answer.first && answer.second == 512.0);
}

TEST(CalculateTest, SimpleExp_5) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string multiplication = "12524.11*1.55";
  answer = calc.CalculateAnswer(multiplication, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, 19412.3705);
}

TEST(CalculateTest, SimpleExp_6) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string multiplication = "-4.587*(-66876.456)";
  answer = calc.CalculateAnswer(multiplication, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, 306762.303672);
}

TEST(CalculateTest, DifficultExp_1) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "ln(42)-tan(45)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, log(42) - tan(45));
}

TEST(CalculateTest, DifficultExp_2) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "2*0.5/1.25/6*3/4";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, (2 * 0.5 / 1.25 / 6 * 3 / 4));
}

TEST(CalculateTest, DifficultExp_3) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "(2^7+3^(-5))*(sqrt(456)/(-6))";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second,
                   (pow(2, 7) + pow(3, -5)) * (sqrt(456) / (-6)));
}

TEST(CalculateTest, DifficultExp_4) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sin(45*4^5/24)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, sin(45 * pow(4, 5) / 24));
}

TEST(CalculateTest, DifficultExp_5) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "ln(45*4^5/24)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, log(45 * pow(4, 5) / 24));
}

TEST(CalculateTest, DifficultExp_6) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "log(1515)^(-1/4)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 0.74882292638, 1E-7);
}

TEST(CalculateTest, DifficultExp_7) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "cos(1515)^(-1/4)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 1.08182179328, 1E-7);
}

TEST(CalculateTest, DifficultExp_8) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "acos(0.2)/5*9-6+3";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, acos(0.2) / 5 * 9 - 6 + 3, 1E-7);
}

TEST(CalculateTest, DifficultExp_9) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "asin(0.52)+ln(2.5412)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, asin(0.52) + log(2.5412), 1E-7);
}

TEST(CalculateTest, DifficultExp_10) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "atan(14)/log(10002211)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, atan(14) / log10(10002211), 1E-7);
}

TEST(CalculateTest, DifficultExp_11) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1024%521+241";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 1024 % 521 + 241, 1E-7);
}

TEST(CalculateTest, DifficultExp_12) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1^2+3-2^1";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 2.0, 1E-7);
}

TEST(CalculateTest, Incorrect_1) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1/";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_2) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1/3+";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}
TEST(CalculateTest, Incorrect_3) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1++";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_4) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "1++546*/+";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_5) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sin()";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_6) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sin(4)*log()";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_7) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "++log(4)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_8) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "/+log(4)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_9) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "/log(4)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_10) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "/log(4)+lala";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_12) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "@3445";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Incorrect_13) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "((";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_FALSE(answer.first);
}

TEST(CalculateTest, Nan_or_Inf_1) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sqrt(-96)";
  answer = calc.CalculateAnswer(expression, 0);
  ASSERT_TRUE(std::isnan(answer.second));
}

TEST(CalculateTest, Whith_x_1) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sqrt(x)";
  answer = calc.CalculateAnswer(expression, 25);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, sqrt(25));
}

TEST(CalculateTest, Whith_x_2) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "x/5+6";
  answer = calc.CalculateAnswer(expression, 5);
  ASSERT_TRUE(answer.first);
  ASSERT_DOUBLE_EQ(answer.second, 7);
}

TEST(CalculateTest, Whith_x_3) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "log(x)+5*6+x/54";
  answer = calc.CalculateAnswer(expression, 4);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 30.6761340654, 1e-7);
}

TEST(CalculateTest, Whith_x_4) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "x^x^x";
  answer = calc.CalculateAnswer(expression, 2);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 16, 1e-7);
}

TEST(CalculateTest, Whith_x_5) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sin(x)";
  answer = calc.CalculateAnswer(expression, 65.2);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, sin(65.2), 1e-7);
}

TEST(CalculateTest, Whith_x_6) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "cos(x)";
  answer = calc.CalculateAnswer(expression, 65.2);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, cos(65.2), 1e-7);
}

TEST(CalculateTest, Whith_x_7) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "cos(x)/sin(54.3)+ln(x)";
  answer = calc.CalculateAnswer(expression, 11254);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 8.44803653736, 1e-7);
}

TEST(CalculateTest, Whith_x8) {
  std::pair<bool, double> answer{};
  s21::Calculate calc;
  std::string expression = "sqrt(x)/tan(x)";
  answer = calc.CalculateAnswer(expression, 41250);
  ASSERT_TRUE(answer.first);
  ASSERT_NEAR(answer.second, 165.026747848, 1e-7);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#include "model.h"

QString s21::Model::ParseLexem(QString result, const QString &lexem,
                               const QString &x_value) {
  s21::Calculate check_operator;
  QString new_label{};
  if (result == "error" || result == "inf" || result == "nan") {
    result.clear();
  }
  if (lexem.back().isDigit()) {
    new_label += s21::Model::Digits(result, lexem);
  } else if (lexem.back() == '.') {
    new_label += s21::Model::Dot(result);
  } else if (lexem.back() == '~') {
    new_label += s21::Model::Negativity(result);
  } else if (check_operator.IsOperator(lexem.back().toLatin1())) {
    new_label += s21::Model::Operations(result, lexem, check_operator);
  } else if (lexem == "()") {
    new_label += s21::Model::Bracets(result, check_operator);
  } else if (lexem == "AC" || lexem == "C") {
    new_label += s21::Model::Clear(result, lexem);
  } else if (lexem.back().isLetter() && lexem != "mod" && lexem != "x") {
    new_label += s21::Model::Fucntions(result, lexem);
  } else if (lexem == "x") {
    new_label += s21::Model::X(result);
  } else if (lexem == "=") {
    new_label += s21::Model::Equal(result, x_value);
  }
  return new_label;
}

void s21::Model::DrawGraphic(QString function_name,
                             std::pair<double, double> x_min_max,
                             std::pair<double, double> y_min_max) {
  s21::Calculate calc;
  std::pair<bool, double> answer{};
  std::string input = function_name.toStdString();
  double step = (x_min_max.second - x_min_max.first) / 10000.0;
  if (function_name.length() < 256) {
    function_name.replace("mod", "%");
    for (double x = x_min_max.first; x <= x_min_max.second; x += step) {
      answer = calc.CalculateAnswer(input, x);
      if (answer.first) {
        if (answer.second > y_min_max.second * 5 ||
            answer.second < y_min_max.first * 5) {
          answer.second = NAN;
        }
        coordinats_.first.push_back(x);
        coordinats_.second.push_back(answer.second);
      }
    }
  }
}

std::array<QString, 3> s21::Model::GetCredit(double summ_of_credit, int month,
                                             double percent,
                                             int type_of_credit) {
  return credit_.CreditCalc(summ_of_credit, month, percent, type_of_credit);
}

int s21::Model::LastNonDigit(QString label, int idx) {
  bool stop = true;
  while (idx >= 0 && stop) {
    if (label.at(idx).isDigit() || label.at(idx) == '.') {
      idx--;
    } else if ((label.at(idx) == '-' || label.at(idx) == '+') &&
               (label.at(idx - 1) == 'e' || label.at(idx - 1) == 'E')) {
      idx--;
    } else {
      stop = false;
    }
  }
  return idx;
}

QString s21::Model::Digits(QString result_line, const QString &digit) {
  QString temp = result_line;
  if (!temp.isEmpty() && (temp.back() == ')' || result_line.back() == 'x')) {
    temp += "*";
  }
  temp += digit;
  return temp;
}

QString s21::Model::Dot(QString result_line) {
  QString temp = result_line;
  int current_char{};
  if (temp.isEmpty() || (!temp.back().isDigit() && !temp.endsWith("."))) {
    temp += "0.";
  } else if (!temp.isEmpty() && temp.back().isDigit()) {
    for (int i = temp.length() - 1; i >= 0; --i) {
      if (!temp.at(i).isDigit() && temp.at(i) != QChar('.')) current_char = i;
    }
    if (!temp.right(current_char - 1).contains('.')) {
      temp += ".";
    }
  }
  return temp;
}

QString s21::Model::X(QString result_line) {
  QString temp = result_line;
  if (!temp.isEmpty() &&
      (temp.back().isDigit() || temp.back() == ')' || temp.back() == 'x')) {
    temp += "*";
  }
  temp += "x";
  return temp;
}

QString s21::Model::Negativity(QString result_line) {
  QString temp = result_line;
  int last_digit_index{};
  s21::Calculate check_operator;
  if (temp.endsWith("(-")) {
    temp.chop(2);
  } else if (temp.endsWith("x")) {
    temp.chop(1);
    temp += "(-x)";
  } else if (temp.endsWith("(-x)")) {
    temp.chop(4);
    temp += "x";
  } else if (temp.isEmpty() ||
             (!temp.isEmpty() &&
              check_operator.IsOperator(temp.back().toLatin1())) ||
             temp.endsWith(")") || temp.endsWith("(")) {
    if (temp.endsWith(")")) {
      temp += "*";
    }
    temp += "(-";
  } else if (!temp.isEmpty() && (temp.back().isDigit() || temp.back() == '.')) {
    last_digit_index = LastNonDigit(temp, temp.length() - 1);
    if (last_digit_index == -1 || !(temp.at(last_digit_index) == '-' &&
                                    temp.at(last_digit_index - 1) == '(')) {
      temp.insert(last_digit_index + 1, "(-");
    } else {
      temp.remove(last_digit_index - 1, 2);
    }
  }

  return temp;
}

QString s21::Model::Operations(QString result_line, const QString &lexem,
                               Calculate check_operator) {
  QString temp = result_line;
  if (temp.isEmpty()) {
    temp += "0";
  }
  QChar last_char = temp.isEmpty() ? QChar() : temp.back();
  if (check_operator.IsOperator(last_char.toLatin1())) {
    if (temp.endsWith("mod")) {
      temp.chop(3);
    } else {
      temp.chop(1);
    }
  }
  if (temp.back() != '(') {
    temp += lexem;
  }
  return temp;
}

QString s21::Model::Fucntions(QString result_line, const QString &lexem) {
  QString temp = result_line;
  if (!temp.isEmpty() &&
      (temp.back().isDigit() || temp.back() == ')' || temp.back() == 'x')) {
    temp += "*";
  }
  temp += lexem + "(";
  return temp;
}

QString s21::Model::Bracets(QString result_line, Calculate check_operator) {
  QString temp = result_line;
  if (temp.isEmpty()) {
    temp.clear();
    temp += "(";
  } else if (temp.count(')') - temp.count('(') == 0) {
    if (!check_operator.IsOperator(temp.back().toLatin1())) {
      temp += "*";
    }
    temp += "(";
  } else {
    if (!check_operator.IsOperator(temp.back().toLatin1()) &&
        temp.back() != '(') {
      temp += ")";
    } else {
      temp += "(";
    }
  }
  return temp;
}

QString s21::Model::Clear(QString result_line, const QString &lexem) {
  QString temp = result_line;
  if (lexem == "AC") {
    temp.clear();
  } else if (lexem == "C") {
    if (!temp.isEmpty() && temp.back() == '(' &&
        temp.at(temp.length() - 2).isLetter()) {
      temp.chop(1);
      int i = result_line.length() - 2;
      while (i >= 0 && temp.at(i).isLetter()) {
        temp.chop(1);
        --i;
      }
    } else if (temp.endsWith("mod")) {
      temp.chop(3);
    } else {
      temp.chop(1);
    }
  }
  return temp;
}

QString s21::Model::Equal(QString result_line, const QString &value_x) {
  s21::Calculate calc;
  std::pair<bool, double> answer;
  QString temp = result_line;
  std::string input;
  if (temp.isEmpty()) {
    temp.clear();
    temp += "0";
  } else {
    if (temp.length() < 256 && temp.count('(') - temp.count(')') == 0) {
      temp.replace("mod", "%");
      input = temp.toStdString();
      answer = calc.CalculateAnswer(input, value_x.toDouble());
      temp.clear();
      if (answer.first) {
        temp = QString::number(answer.second, 'g', 8);
      } else {
        temp = "error";
      }
    } else {
      temp.clear();
      temp = "error";
    }
  }
  return temp;
}

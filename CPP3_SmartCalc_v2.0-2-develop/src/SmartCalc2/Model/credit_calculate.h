#ifndef CPP3_SMARTCALC_V2_MODEL_CREDIT_CALCULATE_H_
#define CPP3_SMARTCALC_V2_MODEL_CREDIT_CALCULATE_H_
#include <qstring.h>

#include <array>
#include <cmath>
#include <iostream>

namespace s21 {
class Credit {
 public:
  Credit() {}
  ~Credit() {}
  std::array<QString, 3> CreditCalc(double summ_of_credit, int month,
                                    double percent, int type_of_credit) {
    std::array<QString, 3> string_result{};
    percent /= 12;
    if (summ_of_credit > 0 && percent >= 0 && percent < 100) {
      if (type_of_credit == 0) {
        per_month_ = summ_of_credit * ((percent * pow((1 + percent), month)) /
                                       (pow((1 + percent), month) - 1));
        sum_ = per_month_ * month;
        string_result[0] = QString::number(per_month_, 'f', 2);
      } else if (type_of_credit == 1) {
        double per_month_pay = summ_of_credit / month;
        for (int i = 0; i < month; ++i) {
          per_month_ =
              (summ_of_credit - (per_month_pay * i)) * percent + per_month_pay;
          sum_ = summ_of_credit + per_month_;
        }
        first_pay_ = summ_of_credit * percent / 12 + per_month_;
        last_pay_ = month != 1 ? (summ_of_credit - (per_month_ * (month - 1))) *
                                         percent +
                                     per_month_
                               : first_pay_;
        string_result[0] = QString::number(first_pay_, 'f', 2);
        string_result[0] += "  ...   ";
        string_result[0] += QString::number(last_pay_, 'f', 2);
      }
      over_pay_ = sum_ - summ_of_credit;
      string_result[1] = QString::number(sum_, 'f', 2);
      string_result[2] = QString::number(over_pay_, 'f', 2);
      PrintNice(&string_result[0], string_result[0].indexOf('.'));
      PrintNice(&string_result[1], string_result[1].indexOf('.'));
      PrintNice(&string_result[2], string_result[2].indexOf('.'));
    } else {
      string_result[0] = "Введите корректные данные";
    }
    return string_result;
  }
  void PrintNice(QString *str, int idx) {
    for (int i{}; idx >= 0; i++) {
      if (i % 3 == 0 && idx != 0) {
        str->insert(idx, ' ');
      }
      idx--;
    }
  }

 private:
  double per_month_{};
  double over_pay_{};
  double sum_{};
  double first_pay_{};
  double last_pay_{};
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_CREDIT_CALCULATE_H_

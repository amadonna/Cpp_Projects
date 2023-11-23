#ifndef CPP3_SMARTCALC_V2_MODEL_CREDIT_MODEL_H_
#define CPP3_SMARTCALC_V2_MODEL_CREDIT_MODEL_H_

#include <qstring.h>

#include <QLineEdit>

#include "calculate.h"
#include "credit_calculate.h"

namespace s21 {
class Model {
 public:
  Model(){};
  //~Model(){};

  QString ParseLexem(QString result, const QString &lexem,
                     const QString &x_value);
  void DrawGraphic(QString function_name, std::pair<double, double> x_min_max,
                   std::pair<double, double> y_min_max);
  std::array<QString, 3> GetCredit(double summ_of_credit, int month,
                                   double percent, int type_of_credit);
  std::pair<std::vector<double>, std::vector<double>> GetCoordinats() {
    return coordinats_;
  }

 private:
  int LastNonDigit(QString label, int idx);
  QString Negativity(QString result_line);
  QString Operations(QString result_line, const QString &lexem,
                     s21::Calculate check_operator);
  QString Fucntions(QString result_line, const QString &lexem);
  QString Bracets(QString result_line, s21::Calculate check_operator);
  QString Digits(QString result_line, const QString &digit);
  QString Clear(QString result_line, const QString &lexem);
  QString Equal(QString result_line, const QString &value_x);
  QString Dot(QString result_line);
  QString X(QString result_line);

  s21::Credit credit_{};
  std::pair<std::vector<double>, std::vector<double>> coordinats_{};
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_CREDIT_MODEL_H_

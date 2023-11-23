#ifndef CPP3_SMARTCALC_V2_CONTROLLER_CONTROLLER_CALC_H_
#define CPP3_SMARTCALC_V2_CONTROLLER_CONTROLLER_CALC_H_

#include <qstring.h>

#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(s21::Model *model) : model_(model) {}
  ~Controller() {}

  QString Controll(QString result, const QString &lexem,
                   const QString &x_value);
  std::pair<std::vector<double>, std::vector<double>> GetCoordinats(
      QString function, std::pair<double, double> x_min_max,
      std::pair<double, double> y_min_max);
  std::array<QString, 3> GetResultOfCredit(double summ_of_credit, int month,
                                           double percent, int type_of_credit);

 private:
  s21::Model *model_;
};
}  // namespace s21

#endif

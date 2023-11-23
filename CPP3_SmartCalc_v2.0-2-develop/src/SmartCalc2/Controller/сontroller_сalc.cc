#include "controller_calc.h"

QString s21::Controller::Controll(QString result, const QString &lexem,
                                  const QString &x_value) {
  return model_->ParseLexem(result, lexem, x_value);
}

std::pair<std::vector<double>, std::vector<double>>
s21::Controller::GetCoordinats(QString function,
                               std::pair<double, double> x_min_max,
                               std::pair<double, double> y_min_max) {
  model_->DrawGraphic(function, x_min_max, y_min_max);
  return model_->GetCoordinats();
}

std::array<QString, 3> s21::Controller::GetResultOfCredit(double summ_of_credit,
                                                          int month,
                                                          double percent,
                                                          int type_of_credit) {
  return model_->GetCredit(summ_of_credit, month, percent, type_of_credit);
}

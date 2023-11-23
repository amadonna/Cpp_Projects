#ifndef CPP3_SMARTCALC_V2_VIEW_GRAPHIC_H_
#define CPP3_SMARTCALC_V2_VIEW_GRAPHIC_H_

#include <QDialog>
#include <QVector>

#include "../Controller/controller_calc.h"

namespace Ui {
class Graphic;
}

class Graphic : public QDialog {
  Q_OBJECT

 public:
  explicit Graphic(s21::Controller *controll, QWidget *parent = nullptr);
  ~Graphic();
 public slots:
  void FunctionNmaeSlot(QString function_name);

 private slots:
  void on_pushButton_ok_clicked();

 private:
  Ui::Graphic *ui;
  s21::Controller *controll_;
};

#endif  // CPP3_SMARTCALC_V2_VIEW_GRAPHIC_H_

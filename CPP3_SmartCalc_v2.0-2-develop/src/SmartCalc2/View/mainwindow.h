#ifndef CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H

#include <QChar>
#include <QLineEdit>
#include <QMainWindow>
#include <QTextStream>
#include <QValidator>
#include <iostream>

#include "../Controller/controller_calc.h"
#include "graphic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controll, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graphic *graph_w_;
  s21::Controller *controller_;
  QDoubleValidator *validator_;
  QIntValidator *validator_1_;
  QLineEdit *CurrentObject();

 private slots:
  void on_pushButton_count_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_g_clicked();
  void digits_numbers();
  void negativity();
  void operations();
  void bracets();
  void cleaner();
  void funcs();
  void eq();
  void x();
 signals:
  void signal(QString);
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H

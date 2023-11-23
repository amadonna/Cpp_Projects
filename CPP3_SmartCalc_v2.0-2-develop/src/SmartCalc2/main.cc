#include <QApplication>
#include <QLabel>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model{};
  s21::Controller controll(&model);
  s21::MainWindow window(&controll);
  window.show();
  window.setWindowTitle("SmartCalc v2.0");
  return a.exec();
}

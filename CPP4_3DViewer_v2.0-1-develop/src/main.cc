#include <QApplication>

#include "view/3d_viewer/widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Model model;
  s21::Controller *controller = s21::Controller::Instance();
  controller->SetModel(&model);
  s21::Widget view(controller);
  view.setWindowTitle("3dViewer v2.0");
  view.show();
  return a.exec();
}

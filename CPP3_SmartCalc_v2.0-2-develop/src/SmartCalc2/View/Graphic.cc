#include "graphic.h"

#include <limits.h>

#include "ui_graphic.h"

Graphic::Graphic(s21::Controller *controll, QWidget *parent)
    : QDialog(parent), ui(new Ui::Graphic), controll_(controll) {
  ui->setupUi(this);
  this->setFixedSize(800, 655);
  ui->x_min->setMinimum(-1000000);
  ui->y_min->setMinimum(-1000000);
  ui->x_max->setMinimum(-1000000);
  ui->y_max->setMinimum(-1000000);
  ui->x_min->setMaximum(1000000);
  ui->y_min->setMaximum(1000000);
  ui->x_max->setMaximum(1000000);
  ui->y_max->setMaximum(1000000);
  ui->x_min->setValue(-10);
  ui->x_max->setValue(10);
  ui->y_min->setValue(-10);
  ui->y_max->setValue(10);

  connect(ui->pushButton_ok, SIGNAL(clicked()), this,
          SLOT(on_pushButton_ok_clicked()));
}

Graphic::~Graphic() { delete ui; }

void Graphic::FunctionNmaeSlot(QString function_name) {
  ui->function_name->setText(function_name);
}

void Graphic::on_pushButton_ok_clicked() {
  ui->graphic_view->xAxis->setRange(ui->x_min->value(), ui->x_max->value());
  ui->graphic_view->yAxis->setRange(ui->y_min->value(), ui->y_max->value());
  std::pair<std::vector<double>, std::vector<double>> coordinats{};
  if (ui->x_min->value() < ui->x_max->value() &&
      ui->y_min->value() < ui->y_max->value()) {
    coordinats = controll_->GetCoordinats(
        ui->function_name->text(),
        std::pair{ui->x_min->value(), ui->x_max->value()},
        std::pair{ui->y_min->value(), ui->y_max->value()});
    QVector<double> x_values(coordinats.first.begin(), coordinats.first.end());
    QVector<double> y_values(coordinats.second.begin(),
                             coordinats.second.end());
    ui->graphic_view->clearGraphs();
    ui->graphic_view->clearItems();
    ui->graphic_view->addGraph();
    ui->graphic_view->graph(0)->addData(x_values, y_values);
    ui->graphic_view->replot();
    x_values.clear();
    y_values.clear();
  }
}

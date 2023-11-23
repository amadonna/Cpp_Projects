#include "mainwindow.h"

#include "graphic.h"
#include "ui_mainwindow.h"

s21::MainWindow::MainWindow(s21::Controller *controll, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controll) {
  ui->setupUi(this);
  validator_1_ = new QIntValidator(parent);
  validator_ = new QDoubleValidator(parent);
  graph_w_ = new Graphic(controller_);
  ui->result->setValidator(validator_);
  ui->result_3->setValidator(validator_);
  ui->lineEdit_sum->setValidator(validator_1_);
  ui->percent->setValidator(validator_);

  ui->result->setFocus();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_neg, SIGNAL(clicked()), this, SLOT(negativity()));

  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_dsub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_openb, SIGNAL(clicked()), this, SLOT(bracets()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(cleaner()));
  connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(cleaner()));

  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(x()));
  connect(ui->pushButton_equel, SIGNAL(clicked()), this, SLOT(eq()));
}

s21::MainWindow::~MainWindow() {
  delete ui;
  delete validator_;
  delete validator_1_;
}

QLineEdit *s21::MainWindow::CurrentObject() {
  return qobject_cast<QLineEdit *>(QApplication::focusWidget());
}

void s21::MainWindow::digits_numbers() {
  CurrentObject()->setText(
      controller_->Controll(CurrentObject()->text(),
                            qobject_cast<QPushButton *>(sender())->text(), ""));
}
void s21::MainWindow::on_pushButton_dot_clicked() {
  CurrentObject()->setText(
      controller_->Controll(CurrentObject()->text(),
                            qobject_cast<QPushButton *>(sender())->text(), ""));
}
void s21::MainWindow::negativity() {
  CurrentObject()->setText(
      controller_->Controll(CurrentObject()->text(), QChar('~'), ""));
}
void s21::MainWindow::operations() {
  if (CurrentObject() == ui->result) {
    ui->result->setText(controller_->Controll(
        ui->result->text(), qobject_cast<QPushButton *>(sender())->text(), ""));
  }
}
void s21::MainWindow::bracets() {
  CurrentObject()->setText(
      controller_->Controll(CurrentObject()->text(),
                            qobject_cast<QPushButton *>(sender())->text(), ""));
}
void s21::MainWindow::cleaner() {
  CurrentObject()->setText(
      controller_->Controll(CurrentObject()->text(),
                            qobject_cast<QPushButton *>(sender())->text(), ""));
}
void s21::MainWindow::funcs() {
  if (CurrentObject() == ui->result) {
    ui->result->setText(controller_->Controll(
        ui->result->text(), qobject_cast<QPushButton *>(sender())->text(), ""));
  }
}
void s21::MainWindow::x() {
  if (CurrentObject() == ui->result) {
    ui->result->setText(controller_->Controll(
        ui->result->text(), qobject_cast<QPushButton *>(sender())->text(), ""));
  }
}

void s21::MainWindow::eq() {
  ui->result->setText(
      controller_->Controll(ui->result->text(), "=", ui->result_3->text()));
}

void s21::MainWindow::on_pushButton_g_clicked() {
  graph_w_->show();
  connect(this, &MainWindow::signal, graph_w_, &Graphic::FunctionNmaeSlot);
  emit signal(ui->result->text());
}

void s21::MainWindow::on_pushButton_count_clicked() {
  std::array<QString, 3> result;
  double month =
      std::strtod(ui->month->currentText().toStdString().c_str(), nullptr);
  if (ui->month->currentText().contains("лет") ||
      ui->month->currentText().contains("год")) {
    month *= 12;
  }
  double sum_credit = ui->lineEdit_sum->text().toDouble();
  double percent = ui->percent->text().toDouble();
  int type = ui->type->currentIndex();
  result =
      controller_->GetResultOfCredit(sum_credit, month, percent / 100, type);
  ui->label_per_m->setText(result[0] +
                           (result[2].size() > 0 && result[2].front().isDigit()
                                ? '\t' + ui->valuta->currentText()
                                : ""));
  ui->label_pereplata->setText(
      result[2] +
      (result[2].size() > 0 ? '\t' + ui->valuta->currentText() : ""));
  ui->label_sum->setText(result[1] + (result[2].size() > 0
                                          ? '\t' + ui->valuta->currentText()
                                          : ""));
}

#include "widget.h"

#include "ui_widget.h"

namespace s21 {

Widget::Widget(Controller *c, QWidget *parent)
    : QOpenGLWidget{parent}, ui_(new Ui::Widget), controller_(c) {
  ui_->setupUi(this);
  LabelSettings();
  file_exists_ = false;
}

Widget::~Widget() {
  delete ui_;
  delete rotation_validator_;
  delete move_validator_;
  delete scale_validator_;
}

void Widget::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users",
                                     "All Files (*.obj)");
  ui_->label_filename->setText(str);
  std::string filename = str.toStdString();
  if (!filename.empty()) {
    if ((file_exists_ = controller_->ReadDataFile(filename))) {
      SetDefaultValues();
      controller_->Normalize();
      ui_->label_Vertexes->setText(
          QString::number(controller_->GetVertexCount() / 3));
      ui_->label_edges->setText(QString::number(controller_->GetEdgesCount()));
      update();
    } else {
      ui_->label_filename->setText("FILE NOT FOUND OR INCORRECT!(");
    }
  }
}

void Widget::SetDefaultValues() {
  ui_->z_rotation->setValue(0);
  ui_->y_rotation->setValue(0);
  ui_->x_rotation->setValue(0);
  ui_->label_x_rot->setText("0");
  ui_->label_y_rot->setText("0");
  ui_->label_z_rot->setText("0");
  ui_->label_x_move->setText("0");
  ui_->label_y_move->setText("0");
  ui_->label_z_move->setText("0");
  ui_->label_scale->setText("0.3");
}

void Widget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Widget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (file_exists_) Draw();
}

void Widget::Draw() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetVertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, controller_->GetFacetsCount(), GL_UNSIGNED_INT,
                 controller_->GetFacets());

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Widget::on_button_scale_down_clicked() {
  double scale_value = ui_->label_scale->text().toDouble();
  if (file_exists_ && scale_value > 0.01) {
    scale_value += kStepDown;
    controller_->ChangeModel("scale", scale_value, 0);
    ui_->label_scale->setText(QString::number(scale_value, 'f', 2));
    update();
  }
}

void Widget::on_button_scale_up_clicked() {
  if (file_exists_) {
    double scale_value = ui_->label_scale->text().toDouble() + kStepUp;
    controller_->ChangeModel("scale", scale_value, 0);
    ui_->label_scale->setText(QString::number(scale_value, 'f', 2));
    update();
  }
}

void Widget::on_label_scale_textEdited(const QString &arg1) {
  double scale_value = arg1.toDouble();
  if (file_exists_ && scale_value > 0.01) {
    controller_->ChangeModel("scale", scale_value, 0);
    update();
  }
}

void Widget::on_x_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kX);
  update();
}

void Widget::on_y_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kY);
  update();
}

void Widget::on_z_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kZ);
  update();
}

void Widget::on_label_x_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kX);
  update();
}

void Widget::on_label_y_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kY);
  update();
}

void Widget::on_label_z_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kZ);
  update();
}

void Widget::on_x_move_down_clicked() {
  double move_step = ui_->label_x_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kX);

  ui_->label_x_move->setText(QString::number(move_step));
  update();
}

void Widget::on_x_move_up_clicked() {
  double move_step = ui_->label_x_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kX);
  ui_->label_x_move->setText(QString::number(move_step));
  update();
}

void Widget::on_y_move_down_clicked() {
  double move_step = ui_->label_y_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kY);
  ui_->label_y_move->setText(QString::number(move_step));
  update();
}

void Widget::on_y_move_up_clicked() {
  double move_step = ui_->label_y_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kY);
  ui_->label_y_move->setText(QString::number(move_step));
  update();
}

void Widget::on_z_move_down_clicked() {
  double move_step = ui_->label_z_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kZ);
  ui_->label_z_move->setText(QString::number(move_step));
  update();
}

void Widget::on_z_move_up_clicked() {
  double move_step = ui_->label_z_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kZ);
  ui_->label_z_move->setText(QString::number(move_step));
  update();
}

void Widget::LabelSettings() {
  rotation_validator_ = new QIntValidator(-180, 180, this);
  ui_->label_x_rot->setValidator(rotation_validator_);
  ui_->label_y_rot->setValidator(rotation_validator_);
  ui_->label_z_rot->setValidator(rotation_validator_);
  move_validator_ = new QDoubleValidator(-1, 1, 2, this);
  move_validator_->setNotation(QDoubleValidator::StandardNotation);
  ui_->label_x_move->setValidator(move_validator_);
  ui_->label_y_move->setValidator(move_validator_);
  ui_->label_z_move->setValidator(move_validator_);
  scale_validator_ = new QDoubleValidator(0.01, 2.5, 2, this);
  scale_validator_->setNotation(QDoubleValidator::StandardNotation);
  ui_->label_scale->setValidator(scale_validator_);
  ConnectLabels();
}

void Widget::ConnectLabels() {
  connect(ui_->x_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui_->label_x_rot->setText(QString::number(ui_->x_rotation->value()));
  });
  connect(ui_->label_x_rot, &QLineEdit::textChanged, this,
          [=] { ui_->x_rotation->setValue(ui_->label_x_rot->text().toInt()); });

  connect(ui_->y_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui_->label_y_rot->setText(QString::number(ui_->y_rotation->value()));
  });
  connect(ui_->label_y_rot, &QLineEdit::textChanged, this,
          [=] { ui_->y_rotation->setValue(ui_->label_y_rot->text().toInt()); });

  connect(ui_->z_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui_->label_z_rot->setText(QString::number(ui_->z_rotation->value()));
  });
  connect(ui_->label_z_rot, &QLineEdit::textChanged, this,
          [=] { ui_->z_rotation->setValue(ui_->label_z_rot->text().toInt()); });
}

}  // namespace s21
#include "controller_singleton.h"

namespace s21 {
Controller *Controller::instance_ = nullptr;

Controller *Controller::Instance() {
  if (!instance_) {
    instance_ = new Controller();
  }
  return instance_;
}
void Controller::SetModel(Model *model) { model_ = model; }
void Controller::Normalize() { model_->Normalize(); }

void Controller::ChangeModel(std::string action, double value, int axis) {
  model_->ChangeModel(action, value, axis);
}

bool Controller::ReadDataFile(std::string &file_name) {
  bool res = true;
  res = model_->ReadDataFile(file_name);
  return res;
}

size_t Controller::GetVertexCount() { return model_->GetVertexCount(); }
size_t Controller::GetEdgesCount() { return model_->GetEdgesCount(); }
unsigned int Controller::GetFacetsCount() { return model_->GetFacetsCount(); }
double *Controller::GetVertexes() { return model_->GetVertexes(); }
unsigned int *Controller::GetFacets() { return model_->GetFacets(); }

}  // namespace s21
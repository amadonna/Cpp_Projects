#include "model_facade.h"

#include <string>
namespace s21 {
void Model::ChangeModel(std::string action, double value, int axis) {
  transform_info_->value = value;
  transform_info_->axis = axis;

  if (action == "rotate") {
    transformation_.Rotate(*object_, *transform_info_);
  } else if (action == "scale" && value != 0) {
    transformation_.Scale(*object_, *transform_info_);
  } else if (action == "move") {
    transformation_.Translate(*object_, *transform_info_);
  }
}

void Model::Clear() {
  if (parcer_ != nullptr) {
    delete parcer_;
  }
  transform_info_->prev_coor = {0};
  transform_info_->prev_angle_x = 0;
  transform_info_->prev_angle_y = 0;
  transform_info_->prev_angle_z = 0;
  object_->count_edges = 0;
  object_->count_facets = 0;
  object_->count_vertex = 0;
  if (!object_->vertexes.empty()) {
    object_->vertexes.clear();
  }
  if (!object_->facets.empty()) {
    object_->facets.clear();
  }
}

bool Model::ReadDataFile(std::string &file_name) {
  Clear();
  bool res = true;
  parcer_ = new Parser(new ReadOne);
  if (parcer_->ReadFile(file_name, object_)) {
    parcer_->setStrategy(new ReadTwo);
    res = parcer_->ReadFile(file_name, object_);
  } else
    res = false;
  return res;
}

unsigned int Model::GetVertexCount() { return object_->count_vertex; }
unsigned int Model::GetEdgesCount() { return object_->count_edges; }
unsigned int Model::GetFacetsCount() { return object_->count_facets * 2; }
double *Model::GetVertexes() { return object_->vertexes.data(); }
unsigned int *Model::GetFacets() { return object_->facets.data(); }

void Model::Normalize() { normalization_.Normalize(*object_); }
}  // namespace s21
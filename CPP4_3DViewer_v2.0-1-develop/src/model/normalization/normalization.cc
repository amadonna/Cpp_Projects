#include "normalization.h"

namespace s21 {

void Normalization::Normalize(DataModel &model) {
  Centering(model);
  Transformation transformation;
  Transform transform{};
  transform.value = kDefaultScale;
  transformation.Scale(model, transform);
}

void Normalization::Centering(DataModel &model) {
  double center_x = GetCenter(GetCoordinates(model, kX));
  double center_y = GetCenter(GetCoordinates(model, kY));
  double center_z = GetCenter(GetCoordinates(model, kZ));
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    model.vertexes[i] -= center_x;
    model.vertexes[i + 1] -= center_y;
    model.vertexes[i + 2] -= center_z;
  }
}

double Normalization::GetCenter(std::vector<double> coordinates) {
  double min = *(std::min_element(coordinates.begin(), coordinates.end()));
  double max = *(std::max_element(coordinates.begin(), coordinates.end()));
  double center = min + (max - min) / 2;
  return center;
}

std::vector<double> Normalization::GetCoordinates(DataModel &model, int axis) {
  std::vector<double> coordinates{};
  for (size_t i = 0; i < model.count_vertex; i += 3) {
    coordinates.push_back(model.vertexes[i + axis]);
  }
  return coordinates;
}

}  // namespace s21
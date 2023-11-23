#include "transformation.h"

namespace s21 {

void Transformation::Scale(DataModel &model, Transform &transform) {
  double scale = 0;
  double max_vertex = 0;
  max_vertex =
      *(std::max_element(model.vertexes.begin(), model.vertexes.end()));
  if (max_vertex != 0)
    scale = (transform.value - transform.value * -1) / max_vertex;
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    model.vertexes[i] *= scale;
    model.vertexes[i + 1] *= scale;
    model.vertexes[i + 2] *= scale;
  }
}

void Transformation::Translate(DataModel &model, Transform &transform) {
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    double tmp = model.vertexes[i + transform.axis];
    model.vertexes[i + transform.axis] =
        tmp + transform.value - transform.prev_coor[transform.axis];
  }
  transform.prev_coor[transform.axis] = transform.value;
}

void Transformation::Rotate(DataModel &model, Transform &transform) {
  double angle = GetAngle(transform);
  double cos_value = cos(angle);
  double sin_value = sin(angle);
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    double temp_x = model.vertexes[i];
    double temp_y = model.vertexes[i + 1];
    double temp_z = model.vertexes[i + 2];
    if (transform.axis == kX) {
      model.vertexes[i + 1] = cos_value * temp_y - sin_value * temp_z;
      model.vertexes[i + 2] = sin_value * temp_y + cos_value * temp_z;
    } else if (transform.axis == kY) {
      model.vertexes[i] = cos_value * temp_x - sin_value * temp_z;
      model.vertexes[i + 2] = sin_value * temp_x + cos_value * temp_z;
    } else if (transform.axis == kZ) {
      model.vertexes[i] = cos_value * temp_x - sin_value * temp_y;
      model.vertexes[i + 1] = sin_value * temp_x + cos_value * temp_y;
    }
  }
  SavePrevAngle(transform);
}

double Transformation::GetAngle(Transform &transform) {
  double angle = 0;
  double pr_a = 0;
  angle = transform.value * kConvertAngle;
  if (transform.axis == kX) {
    pr_a = transform.prev_angle_x * kConvertAngle;
  } else if (transform.axis == kY) {
    pr_a = transform.prev_angle_y * kConvertAngle;
  } else if (transform.axis == kZ) {
    pr_a = transform.prev_angle_z * kConvertAngle;
  }
  return angle - pr_a;
}

void Transformation::SavePrevAngle(Transform &transform) {
  if (transform.axis == kX) {
    transform.prev_angle_x = transform.value;
  } else if (transform.axis == kY) {
    transform.prev_angle_y = transform.value;
  } else if (transform.axis == kZ) {
    transform.prev_angle_z = transform.value;
  }
}
}  // namespace s21
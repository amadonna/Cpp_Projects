#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_TRANSFORM_TRANSFORMATION_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_TRANSFORM_TRANSFORMATION_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "../data/data_model.h"

namespace s21 {

class Transformation {
 public:
  Transformation() {}
  ~Transformation() {}
  void Rotate(DataModel &model, Transform &transform);
  void Scale(DataModel &model, Transform &transform);
  void Translate(DataModel &model, Transform &transform);

 private:
  static constexpr double kConvertAngle = M_PI / 180;
  double GetAngle(Transform &transform);
  void SavePrevAngle(Transform &transform);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_TRANSFORM_TRANSFORMATION_H
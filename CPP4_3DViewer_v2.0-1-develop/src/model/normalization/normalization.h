#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_NORMALIZATION_NORMALIZATION_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_NORMALIZATION_NORMALIZATION_H_

#include "../transform/transformation.h"

namespace s21 {
class Normalization {
 public:
  Normalization() {}
  ~Normalization() {}
  void Normalize(DataModel &model);

 private:
  void Centering(DataModel &model);
  double GetCenter(std::vector<double> coordinates);
  std::vector<double> GetCoordinates(DataModel &model, int axis);
  static constexpr double kDefaultScale = 0.3;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_NORMALIZATION_NORMALIZATION_H_

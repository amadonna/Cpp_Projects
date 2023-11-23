#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_

#include "normalization/normalization.h"
#include "parcer/parcer.h"

namespace s21 {

class Model {
 public:
  Model() {
    object_ = new DataModel;
    transform_info_ = new Transform;
    parcer_ = nullptr;
  }

  ~Model() {
    delete object_;
    delete transform_info_;
    delete parcer_;
  }
  void ChangeModel(std::string action, double value, int axis);
  void Normalize();

  unsigned int GetVertexCount();
  unsigned int GetEdgesCount();
  unsigned int GetFacetsCount();
  void Clear();
  double *GetVertexes();
  unsigned int *GetFacets();

  bool ReadDataFile(std::string &file_name);

 private:
  Normalization normalization_{};
  Transformation transformation_;
  DataModel *object_;
  Transform *transform_info_;
  Parser *parcer_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_

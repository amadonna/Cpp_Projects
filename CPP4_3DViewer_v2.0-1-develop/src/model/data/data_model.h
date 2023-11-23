#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_DATA_DATA_MODEL_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_DATA_DATA_MODEL_H_

#include <array>
#include <vector>

namespace s21 {

enum Axis { kX, kY, kZ };

struct DataModel {
  unsigned int count_vertex;
  unsigned int count_facets;
  unsigned int count_edges;
  std::vector<double> vertexes;
  std::vector<unsigned int> facets;
};

struct Transform {
  double value;
  int axis;
  double prev_angle_x;
  double prev_angle_y;
  double prev_angle_z;

  std::array<double, 3> prev_coor;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_DATA_DATA_MODEL_H_
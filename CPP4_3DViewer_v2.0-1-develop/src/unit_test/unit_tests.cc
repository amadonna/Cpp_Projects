#include <gtest/gtest.h>

#include <filesystem>

#include "../model/model_facade.h"

TEST(ViewerTest, Test_1) {
  std::string file_name = "";
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_EQ(model.GetEdgesCount(), 0);
  EXPECT_EQ(model.GetVertexCount(), 0);
  EXPECT_EQ(model.GetFacetsCount(), 0);
};

TEST(ViewerTest, Test_2) {
  std::string file_name = std::filesystem::absolute("cube.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_EQ(model.GetEdgesCount(), 10);
  EXPECT_EQ(model.GetVertexCount(), 24);
  EXPECT_EQ(model.GetFacetsCount(), 60);
  EXPECT_NEAR(model.GetVertexes()[model.GetEdgesCount()], 2, 1e-5);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 6);

  file_name.clear();
  file_name = std::filesystem::absolute("lamp.obj");
  model.ReadDataFile(file_name);
  EXPECT_EQ(model.GetEdgesCount(), 4403);
  EXPECT_EQ(model.GetVertexCount(), 13320);
  EXPECT_EQ(model.GetFacetsCount(), 35262);
  EXPECT_NEAR(model.GetVertexes()[model.GetEdgesCount()], -1.42317, 1e-5);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 1680);
};

TEST(ViewerTest, Test_3) {
  std::string file_name = std::filesystem::absolute("cube.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_EQ(model.GetVertexes()[12], 2);
  EXPECT_EQ(model.GetVertexes()[13], 0);
  EXPECT_EQ(model.GetVertexes()[14], 0);
  model.ChangeModel("scale", 0.3, 0);
  EXPECT_EQ(model.GetVertexes()[12], 0.6);
  EXPECT_EQ(model.GetVertexes()[13], 0);
  EXPECT_EQ(model.GetVertexes()[14], 0);
};

TEST(ViewerTest, Test_4) {
  std::string file_name = std::filesystem::absolute("lamp.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_NEAR(model.GetVertexes()[12], 0.144946, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38004, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], -0.144946, 1e-5);
  double value = 90.0 / 180.0 * 3.1415926535;
  model.ChangeModel("rotate", value, 1);
  EXPECT_NEAR(model.GetVertexes()[12], 0.14886, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38004, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], -0.14091, 1e-5);
};

TEST(ViewerTest, Test_5) {
  std::string file_name = std::filesystem::absolute("female.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_NEAR(model.GetVertexes()[12], -0.08900, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 12.13809, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], 1.34065, 1e-5);
  double value = 90.0 / 180.0 * 3.1415926535;
  model.ChangeModel("move", value, 1);
  EXPECT_NEAR(model.GetVertexes()[12], -0.08900, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 13.70888, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], 1.34065, 1e-5);
};

TEST(ViewerTest, Test_6) {
  std::string file_name = std::filesystem::absolute("lamp.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  model.Normalize();
  EXPECT_NEAR(model.GetVertexes()[0], -0.0480381, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[1], 0.6, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[2], 0, 1e-5);
};

TEST(ViewerTest, Test_7) {
  std::string file_name = std::filesystem::absolute("lamp.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_NEAR(model.GetVertexes()[12], 0.144946, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38004, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], -0.144946, 1e-5);
  double value = 90.0 / 180.0 * 3.1415926535;
  model.ChangeModel("rotate", value, 0);
  EXPECT_NEAR(model.GetVertexes()[12], 0.144946, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38086, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], 0.084823, 1e-5);
};

TEST(ViewerTest, Test_8) {
  std::string file_name = std::filesystem::absolute("lamp.obj");
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_NEAR(model.GetVertexes()[12], 0.144946, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38004, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], -0.144946, 1e-5);
  double value = 90.0 / 180.0 * 3.1415926535;
  model.ChangeModel("rotate", value, 2);
  EXPECT_NEAR(model.GetVertexes()[12], -0.084823, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[13], 8.38086, 1e-5);
  EXPECT_NEAR(model.GetVertexes()[14], -0.144946, 1e-5);
};

TEST(ViewerTest, Test_9) {
  std::string file_name = std::filesystem::absolute("nofile.obj");
  s21::Model model;
  EXPECT_FALSE(model.ReadDataFile(file_name));
};

TEST(ViewerTest, Test_10) {
  std::string file_name = std::filesystem::absolute("negative.obj");
  s21::Model model;
  EXPECT_FALSE(model.ReadDataFile(file_name));
};

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

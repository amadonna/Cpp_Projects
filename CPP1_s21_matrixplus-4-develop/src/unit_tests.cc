#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestGroupName, DefaultConst_1) {
  S21Matrix temp;
  ASSERT_EQ(temp.GetCol(), 0);
  ASSERT_EQ(temp.GetRow(), 0);
}

TEST(TestGroupName, ConstWithParam) {
  S21Matrix temp(5);
  S21Matrix temp_1(15);
  S21Matrix temp_2(0);
  ASSERT_EQ(temp.GetCol(), 5);
  ASSERT_EQ(temp.GetRow(), 5);
  ASSERT_EQ(temp_1.GetCol(), 15);
  ASSERT_EQ(temp_1.GetRow(), 15);
  ASSERT_EQ(temp_2.GetCol(), 0);
  ASSERT_EQ(temp_2.GetRow(), 0);
  try {
    S21Matrix A(-5);
  } catch (std::invalid_argument const& ex) {
    ASSERT_STREQ(ex.what(), "Argument is less than 1");
  }
}
TEST(TestGroupName, ConstWithParams) {
  try {
    S21Matrix A(-5, 1);
  } catch (std::invalid_argument const& ex) {
    ASSERT_STREQ(ex.what(), "Argument is less than 1");
  }
  try {
    S21Matrix B(1, -5);
  } catch (std::invalid_argument const& ex) {
    ASSERT_STREQ(ex.what(), "Argument is less than 1");
  }
}
TEST(TestGroupName, ConstWithParams_1) {
  S21Matrix temp(10, 10);
  S21Matrix temp_1(0, 0);
  S21Matrix temp_2(0, 10);
  S21Matrix temp_3(10, 0);
  ASSERT_EQ(temp.GetCol(), 10);
  ASSERT_EQ(temp.GetRow(), 10);
  ASSERT_EQ(temp_1.GetCol(), 0);
  ASSERT_EQ(temp_1.GetRow(), 0);
  ASSERT_EQ(temp_2.GetCol(), 0);
  ASSERT_EQ(temp_2.GetRow(), 0);
  ASSERT_EQ(temp_3.GetCol(), 0);
  ASSERT_EQ(temp_3.GetRow(), 0);
}
TEST(TestGroupName, CopyConst) {
  S21Matrix temp(10, 10);
  temp.SetMatrix(1.5, 20.3);
  S21Matrix temp_1(temp);
  double n = 1.5;
  ASSERT_EQ(temp_1.GetRow(), 10);
  ASSERT_EQ(temp_1.GetCol(), 10);
  for (int i = 0; i < temp_1.GetRow(); ++i) {
    for (int j = 0; j < temp_1.GetCol(); ++j) {
      ASSERT_EQ(temp_1(i, j), n);
      n += 20.3;
    }
  }
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix source(3, 3);
  source.SetMatrix(1.0, 1.0);
  S21Matrix copy(source);
  S21Matrix moved(std::move(source));
  ASSERT_EQ(moved.GetRow(), 3);
  ASSERT_EQ(moved.GetCol(), 3);
  for (int i = 0; i < moved.GetRow(); ++i) {
    for (int j = 0; j < moved.GetCol(); ++j) {
      ASSERT_EQ(moved(i, j), copy(i, j));
    }
  }
  ASSERT_EQ(source.GetRow(), 0);
  ASSERT_EQ(source.GetCol(), 0);
}

TEST(S21MatrixTest, CopyAssignmentOperatorNonConst) {
  S21Matrix mat1(2, 2);
  mat1.SetMatrix(1.0, 1.0);
  S21Matrix mat2(1, 1);
  mat2 = mat1;
  ASSERT_EQ(mat1.GetRow(), 2);
  ASSERT_EQ(mat1.GetCol(), 2);
  ASSERT_EQ(mat2.GetRow(), 2);
  ASSERT_EQ(mat2.GetCol(), 2);
  S21Matrix temp_1(3, 3);
  mat1 = temp_1;
  mat1(0, 0) = 2.0;
  ASSERT_NE(mat1(0, 0), mat2(0, 0));
}

TEST(S21MatrixTest, CopyAssignmentOperatorConst) {
  const S21Matrix mat1(6, 6);
  S21Matrix mat2(1, 1);
  mat2 = mat1;
  // Check that the copied matrix is identical to the original
  ASSERT_EQ(mat1.GetRow(), mat2.GetRow());
  ASSERT_EQ(mat1.GetCol(), mat2.GetCol());
  for (int i = 0; i < mat1.GetRow(); ++i) {
    for (int j = 0; j < mat1.GetCol(); ++j) {
      ASSERT_EQ(mat1(i, j), mat2(i, j));
    }
  }
}

TEST(S21MatrixTest, EqMatrix) {
  // Test matrices with different sizes
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  ASSERT_THROW(m1.EqMatrix(m2), std::range_error);
  // ASSERT_FALSE(m1.EqMatrix(m2));

  // Test matrices with same size but different elements
  S21Matrix m3(2, 2);
  S21Matrix m4(2, 2);
  m3.SetMatrix(1, 1);
  m4.SetMatrix(2, 1);
  ASSERT_FALSE(m3.EqMatrix(m4));

  // Test matrices with same size and same elements
  S21Matrix m5(24, 24);
  S21Matrix m6(24, 24);
  m5.SetMatrix(1.01445, 1.2);
  m6.SetMatrix(1.01445, 1.2);
  ASSERT_TRUE(m5.EqMatrix(m6));

  // Test matrices with same size and very small difference between elements
  S21Matrix m7(2, 2);
  S21Matrix m8(2, 2);
  m7.SetMatrix(1, 1e-10);
  m8.SetMatrix(1 + 1e-20, 1e-10);
  ASSERT_TRUE(m7.EqMatrix(m8));

  // Test matrices with same size and large difference between elements
  S21Matrix m9(2, 2);
  S21Matrix m10(2, 2);
  m9.SetMatrix(1, 1);
  m10.SetMatrix(1e9, 1);
  ASSERT_FALSE(m9.EqMatrix(m10));

  S21Matrix m11(15, 15);
  S21Matrix m12(15, 15);
  m9.SetMatrix(1524.01245127, 10.245154);
  m10.SetMatrix(1524.01245123, 10.245154);
  ASSERT_TRUE(m11.EqMatrix(m12));

  S21Matrix m13;
  S21Matrix m14;
  ASSERT_TRUE(m13.EqMatrix(m14));
}

TEST(SumMatrixTest, DifferentSize) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  ASSERT_THROW(mat1.SumMatrix(mat2), std::range_error);
}

TEST(SumMatrixTest, SameSize) {
  S21Matrix mat1(2, 2);
  mat1.SetMatrix(1, 1);
  S21Matrix mat2(2, 2);
  mat2.SetMatrix(2, 2);
  mat1.SumMatrix(mat2);
  ASSERT_EQ(mat1(0, 0), 3);
  ASSERT_EQ(mat1(0, 1), 6);
  ASSERT_EQ(mat1(1, 0), 9);
  ASSERT_EQ(mat1(1, 1), 12);
}
TEST(SumMatrixTest, EmptyMatrix) {
  S21Matrix mat1(2, 2);
  mat1.SetMatrix(1, 1);
  S21Matrix mat2;
  ASSERT_THROW(mat1.SumMatrix(mat2), std::range_error);
}

TEST(SumMatrixTest, SameMatrix) {
  int n = 14512, step = -65412;
  S21Matrix mat1(10, 10);
  mat1.SetMatrix(n, step);
  S21Matrix mat2(mat1);
  mat1.SumMatrix(mat2);
  for (int i = 0; i < mat1.GetRow(); ++i) {
    for (int j = 0; j < mat1.GetCol(); ++j) {
      ASSERT_EQ(mat1(i, j), n * 2);
      n += step;
    }
  }
}

TEST(SubMatrixTest, DifferentSize) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  ASSERT_THROW(mat1.SubMatrix(mat2), std::range_error);
}

TEST(SubMatrixTest, SameSize) {
  S21Matrix mat1(2, 2);
  mat1.SetMatrix(1, 1);
  S21Matrix mat2(2, 2);
  mat2.SetMatrix(2, 2);
  mat1.SubMatrix(mat2);
  ASSERT_EQ(mat1(0, 0), -1);
  ASSERT_EQ(mat1(0, 1), -2);
  ASSERT_EQ(mat1(1, 0), -3);
  ASSERT_EQ(mat1(1, 1), -4);
}
TEST(SubMatrixTest, EmptyMatrix) {
  S21Matrix mat1(2, 2);
  mat1.SetMatrix(1, 1);
  S21Matrix mat2;
  ASSERT_THROW(mat1.SubMatrix(mat2), std::range_error);
}

TEST(SubMatrixTest, SameMatrix) {
  double n = 14512, step = -65412;
  S21Matrix mat1(10, 10);
  mat1.SetMatrix(n, step);
  S21Matrix mat2(mat1);
  mat1.SubMatrix(mat2);
  for (int i = 0; i < mat1.GetRow(); ++i) {
    for (int j = 0; j < mat1.GetCol(); ++j) {
      ASSERT_EQ(mat1(i, j), 0);
      n -= step;
    }
  }
}

TEST(MulNumMatrixTest, SimpleMul) {
  double n = 10.23, step = 20.457, m = 6.3;
  S21Matrix mat(15, 15);
  mat.SetMatrix(n, step);
  mat.MulNumber(m);
  for (int i = 0; i < mat.GetRow(); ++i) {
    for (int j = 0; j < mat.GetCol(); ++j) {
      ASSERT_DOUBLE_EQ(mat(i, j), n * m);
      n += step;
    }
  }
}

TEST(MulNumMatrixTest, ZeroMul) {
  double n = 10.23, step = 20.457, m = 0;
  S21Matrix mat(15, 15);
  mat.SetMatrix(n, step);
  mat.MulNumber(m);
  for (int i = 0; i < mat.GetRow(); ++i) {
    for (int j = 0; j < mat.GetCol(); ++j) {
      ASSERT_DOUBLE_EQ(mat(i, j), 0);
      n += step;
    }
  }
}

TEST(S21MatrixTest, MulMatrixNormal) {
  S21Matrix m1(2, 3);
  m1.SetMatrix(1, 1);
  S21Matrix m2(3, 2);
  m2.SetMatrix(7, 1);
  m1.MulMatrix(m2);
  ASSERT_EQ(m1.GetCol(), 2);
  ASSERT_EQ(m1.GetRow(), 2);
  ASSERT_DOUBLE_EQ(m1(0, 0), 58);
  ASSERT_DOUBLE_EQ(m1(0, 1), 64);
  ASSERT_DOUBLE_EQ(m1(1, 0), 139);
  ASSERT_DOUBLE_EQ(m1(1, 1), 154);
}

TEST(S21MatrixTest, MulMatrixDiffSize) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 6);

  ASSERT_THROW(m1.MulMatrix(m2), std::range_error);
}

TEST(S21MatrixTest, TransposeSquareMatrix) {
  int r = 4, c = 4, n = 10, step = 20;
  S21Matrix mat(r, c);
  mat.SetMatrix(n, step);
  S21Matrix transposed = mat.Transpose();
  ASSERT_EQ(transposed.GetRow(), c);
  ASSERT_EQ(transposed.GetCol(), r);
  for (int j = 0; j < transposed.GetCol(); ++j) {
    for (int i = 0; i < transposed.GetRow(); ++i) {
      ASSERT_EQ(transposed(i, j), n);
      n += step;
    }
  }
}

TEST(S21Matrix_Det, DetTest_1) {
  S21Matrix m(1, 1);
  m(0, 0) = 2;
  ASSERT_EQ(m.Determinant(), 2);
}

TEST(S21Matrix_Det, DetTest_2) {
  S21Matrix m(2, 2);
  m(0, 0) = 2;
  m(0, 1) = 4;
  m(1, 0) = 5;
  m(1, 1) = 4;
  ASSERT_EQ(m.Determinant(), -12);
}
TEST(S21Matrix_Det, DetTest_3) {
  S21Matrix m(5, 5);
  m.SetMatrix(1, 1);
  m(0, 0) = 2;
  m(0, 1) = 4;
  m(1, 0) = 45;
  m(1, 1) = 46;
  m(4, 4) = 2;
  ASSERT_EQ(m.Determinant(), -4485);
}

TEST(S21Matrix_Det, DetTest_4) {
  S21Matrix m(5, 2);
  ASSERT_THROW(m.Determinant(), std::range_error);
}

TEST(S21Matrix_Det, Calc_Comp_1) {
  S21Matrix m(5, 2);
  ASSERT_THROW(m.CalcComplements(), std::range_error);
}
TEST(S21Matrix_Det, Calc_Comp_1_0) {
  S21Matrix m(1, 1);
  ASSERT_EQ(m.CalcComplements()(0, 0), m(0, 0));
  ASSERT_EQ(m.CalcComplements().GetRow(), 1);
  ASSERT_EQ(m.CalcComplements().GetCol(), 1);
}

TEST(S21Matrix_Det, Calc_Comp_2) {
  S21Matrix t(3, 3);
  S21Matrix t_1(3, 3);
  t(0, 0) = 1;
  t(0, 1) = 2;
  t(0, 2) = 3;
  t(1, 0) = 0;
  t(1, 1) = 4;
  t(1, 2) = 2;
  t(2, 0) = 5;
  t(2, 1) = 2;
  t(2, 2) = 1;
  t_1(0, 0) = 0;
  t_1(0, 1) = 10;
  t_1(0, 2) = -20;
  t_1(1, 0) = 4;
  t_1(1, 1) = -14;
  t_1(1, 2) = 8;
  t_1(2, 0) = -8;
  t_1(2, 1) = -2;
  t_1(2, 2) = 4;
  ASSERT_TRUE(t_1.EqMatrix(t.CalcComplements()));
}

TEST(S21MatrixInverse, Inverse_1) {
  S21Matrix t(3, 3);
  t.SetMatrix(1, 1);
  ASSERT_THROW(t.InverseMatrix(), std::range_error);
}

TEST(S21MatrixInverse, Inverse_2) {
  S21Matrix t(2, 2);
  S21Matrix t_1(2, 2);
  t(0, 0) = 2;
  t(0, 1) = 3;
  t(1, 0) = 4;
  t(1, 1) = 5;
  t_1(0, 0) = 5.0 / -2.0;
  t_1(0, 1) = -3.0 / -2.0;
  t_1(1, 0) = -4.0 / -2.0;
  t_1(1, 1) = 2.0 / -2.0;
  ASSERT_TRUE(t_1.EqMatrix(t.InverseMatrix()));
}

TEST(S21MatrixInverse, Inverse_3) {
  S21Matrix t(3, 3);
  S21Matrix t_1(3, 3);
  t(0, 0) = 2;
  t(0, 1) = 5;
  t(0, 2) = 7;
  t(1, 0) = 6;
  t(1, 1) = 3;
  t(1, 2) = 4;
  t(2, 0) = 5;
  t(2, 1) = -2;
  t(2, 2) = -3;

  t_1(0, 0) = 1;
  t_1(0, 1) = -1;
  t_1(0, 2) = 1;
  t_1(1, 0) = -38;
  t_1(1, 1) = 41;
  t_1(1, 2) = -34;
  t_1(2, 0) = 27;
  t_1(2, 1) = -29;
  t_1(2, 2) = 24;
  ASSERT_TRUE(t_1.EqMatrix(t.InverseMatrix()));
}
TEST(S21MatrixTest, EqualsOperator) {
  S21Matrix A(5, 5);
  A.SetMatrix(10.2, 1);
  S21Matrix B(5, 5);
  B.SetMatrix(10.2, 1);
  S21Matrix C(5, 5);
  C.SetMatrix(17, 12);
  ASSERT_TRUE(A == B);
  ASSERT_FALSE(A == C);
}
TEST(S21MatrixTest, SumOperator) {
  double n = 10.2, step = 1.120;
  S21Matrix A(5, 5);
  A.SetMatrix(n, step);
  S21Matrix B(5, 5);
  B.SetMatrix(n, step);
  A += B;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      ASSERT_EQ(A(i, j), n * 2);
      n += step;
    }
  }
}

TEST(S21MatrixTest, SubOperator) {
  double n = 10.2, step = 1.120;
  S21Matrix A(5, 5);
  A.SetMatrix(n, step);
  S21Matrix B(5, 5);
  B.SetMatrix(n, step);
  A -= B;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      ASSERT_EQ(A(i, j), 0);
    }
  }
}

TEST(S21MatrixTest, MulOperator) {
  S21Matrix m1(2, 3);
  m1.SetMatrix(1, 1);
  S21Matrix m2(3, 2);
  m2.SetMatrix(7, 1);
  m1 *= m2;
  ASSERT_DOUBLE_EQ(m1(0, 0), 58);
  ASSERT_DOUBLE_EQ(m1(0, 1), 64);
  ASSERT_DOUBLE_EQ(m1(1, 0), 139);
  ASSERT_DOUBLE_EQ(m1(1, 1), 154);
}

TEST(S21MatrixTest, MulNumOperator) {
  int n = 15, step = 25;
  S21Matrix temp(6, 6);
  temp.SetMatrix(n, step);
  temp *= 0.6;
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ(temp(i, j), n * 0.6);
      n += step;
    }
  }
}
TEST(S21MatrixTest, BrOperator) {
  int n = 15, step = 25;
  S21Matrix temp(6, 6);
  temp.SetMatrix(n, step);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ(temp(i, j), n);
      n += step;
    }
  }
  ASSERT_THROW(temp(-1, 1), std::range_error);
  ASSERT_THROW(temp(1, -1), std::range_error);
  const S21Matrix a1(1, 1);
  ASSERT_THROW(a1(1, -1), std::range_error);
}

TEST(S21MatrixTest, PlusOperator) {
  int n = 15, step = 25;
  S21Matrix temp(6, 6);
  temp.SetMatrix(n, step);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ((temp + temp)(i, j), n * 2);
      n += step;
    }
  }
}

TEST(S21MatrixTest, MinusOperator) {
  int n = 15, step = 25;
  S21Matrix temp(6, 6);
  temp.SetMatrix(n, step);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ((temp - temp)(i, j), 0);
    }
  }
}

TEST(S21MatrixTest, Mul_1_Operator) {
  int n = 15, step = 25;
  S21Matrix temp(6, 6);
  temp.SetMatrix(n, step);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ((temp * 0.5)(i, j), n * 0.5);
      n += step;
    }
  }
}

TEST(S21MatrixTest, Mul_3_Operator) {
  S21Matrix m1(2, 3);
  m1.SetMatrix(1, 1);
  S21Matrix m2(3, 2);
  m2.SetMatrix(7, 1);
  ASSERT_DOUBLE_EQ((m1 * m2)(0, 0), 58);
  ASSERT_DOUBLE_EQ((m1 * m2)(0, 1), 64);
  ASSERT_DOUBLE_EQ((m1 * m2)(1, 0), 139);
  ASSERT_DOUBLE_EQ((m1 * m2)(1, 1), 154);
}
TEST(S21MatrixTest, Set_Row_Col) {
  S21Matrix m1(1, 1);
  m1.SetCol(5);
  m1.SetRow(10);
  ASSERT_EQ(m1.GetRow(), 10);
  ASSERT_EQ(m1.GetCol(), 5);
  ASSERT_THROW(m1.SetRow(-1), std::invalid_argument);
  m1.SetCol(0);
  ASSERT_EQ(m1.GetCol(), 0);
  S21Matrix m2(2, 2);
  ASSERT_THROW(m2.SetCol(-1), std::invalid_argument);
  m2.SetRow(0);
  ASSERT_EQ(m2.GetRow(), 0);
  S21Matrix m3(20, 20);
  m3.SetRow(11);
  m3.SetCol(12);
  ASSERT_EQ(m3.GetCol(), 12);
  ASSERT_EQ(m3.GetRow(), 11);
  m3.SetRow(0);
  ASSERT_THROW(m3.SetCol(1), std::invalid_argument);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
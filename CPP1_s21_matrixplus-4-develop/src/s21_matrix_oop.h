#ifndef CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();  // Default constructor
  S21Matrix(int size_matrix);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();  // Destructor
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const double& other);
  void operator*=(const S21Matrix& other);
  double& operator()(int index_row, int index_col);
  double operator()(int index_row, int index_col) const;
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant();
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  void SetMatrix(double begin, double range);
  void SetRow(int size_of_rows);
  void SetCol(int size_of_cols);
  int GetRow() const;
  int GetCol() const;

 private:
  int rows_, cols_;
  double** matrix_;

  constexpr static double epsilon_ = 1e-7;
  void CreateMatrix(int rows, int cols);
  void RemoveMatrix();
  void ReleaseMatrix();
  void CopyMatrix(const S21Matrix& dest);
  bool CheckForSameSize(const S21Matrix& first);
  bool CheckSquare();
  void CutMatrix(S21Matrix& dest, int row, int col);
};

#endif  // CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H

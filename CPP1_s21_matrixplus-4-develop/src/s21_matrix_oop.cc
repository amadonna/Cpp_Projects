#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() { ReleaseMatrix(); }
S21Matrix::S21Matrix(int size_matrix) {
  CreateMatrix(size_matrix, size_matrix);
}
S21Matrix::S21Matrix(int rows, int cols) { CreateMatrix(rows, cols); }
S21Matrix::S21Matrix(const S21Matrix& other) {
  if (this != &other) {
    CreateMatrix(other.rows_, other.cols_);
    CopyMatrix(other);
  }
}
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.ReleaseMatrix();
}
S21Matrix::~S21Matrix() { RemoveMatrix(); }

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.ReleaseMatrix();
  }
  return *this;
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    RemoveMatrix();
    CreateMatrix(other.rows_, other.cols_);
    CopyMatrix(other);
  }
  return *this;
}
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }
void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }
void S21Matrix::operator*=(const double& other) { MulNumber(other); }
double& S21Matrix::operator()(int index_row, int index_col) {
  if (index_row >= rows_ || index_col >= cols_ || index_col < 0 ||
      index_row < 0)
    throw std::range_error("Invalid index");
  return matrix_[index_row][index_col];
}
double S21Matrix::operator()(int index_row, int index_col) const {
  if (index_row >= rows_ || index_col >= cols_ || index_col < 0 ||
      index_row < 0)
    throw std::range_error("Invalid index");
  return matrix_[index_row][index_col];
}
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result += other;
  return result;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result -= other;
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result *= other;
  return result;
}
S21Matrix S21Matrix::operator*(const double& other) {
  S21Matrix result(*this);
  result *= other;
  return result;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = false;
  int matched_elements = 0;
  if (!CheckForSameSize(other))
    throw std::range_error("different matrix dimensions");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) <= epsilon_) {
        matched_elements++;
      }
    }
  }
  result = (matched_elements == rows_ * cols_);
  return result;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!CheckForSameSize(other))
    throw std::range_error("different matrix dimensions");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!CheckForSameSize(other))
    throw std::range_error("different matrix dimensions");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) matrix_[i][j] *= num;
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::range_error("Different matrix dimensions");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}
double S21Matrix::Determinant() {
  double det = 0;
  if (!CheckSquare()) throw std::range_error("Different matrix dimensions");
  S21Matrix temp;
  if (rows_ == 1)
    det = matrix_[0][0];
  else if (rows_ == 2)
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else if (rows_ > 2) {
    for (int k = 0; k < rows_; ++k) {
      temp.CreateMatrix(rows_ - 1, cols_ - 1);
      CutMatrix(temp, 0, k);
      det += pow(-1, k) * matrix_[0][k] * temp.Determinant();
      temp.RemoveMatrix();
    }
  }
  return det;
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}
S21Matrix S21Matrix::CalcComplements() {
  if (!CheckSquare()) throw std::range_error("Different matrix dimensions");
  S21Matrix result(rows_, cols_);
  S21Matrix temp(rows_ - 1, cols_ - 1);
  if (rows_ == 1)
    result.matrix_[0][0] = matrix_[0][0];
  else if (rows_ > 1) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < rows_; ++j) {
        CutMatrix(temp, i, j);
        result.matrix_[i][j] = pow(-1, i + j) * temp.Determinant();
      }
    }
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  double det = 0;
  if ((det = this->Determinant()) == 0)
    throw std::range_error("different matrix dimensions");
  S21Matrix result(rows_, cols_);
  S21Matrix transposed;
  transposed = this->Transpose();
  for (int i = 0; i < transposed.rows_; ++i) {
    for (int j = 0; j < transposed.cols_; ++j) {
      result.matrix_[i][j] = transposed.CalcComplements().matrix_[i][j] / det;
    }
  }
  return result;
}

int S21Matrix::GetRow() const { return rows_; }
int S21Matrix::GetCol() const { return cols_; }
void S21Matrix::SetRow(int size_of_rows) {
  S21Matrix temp(*this);
  if (size_of_rows < 0) {
    throw std::invalid_argument("Argument is less than 0");
  }
  if (size_of_rows == 0) {
    RemoveMatrix();
  } else if (rows_ != size_of_rows) {
    RemoveMatrix();
    CreateMatrix(size_of_rows, temp.cols_);
    for (int i = 0; i < (size_of_rows < temp.rows_ ? size_of_rows : temp.rows_);
         i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = temp.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::SetCol(int size_of_cols) {
  S21Matrix temp(*this);
  if (size_of_cols < 0) {
    throw std::invalid_argument("Argument is less than 0");
  }
  if (size_of_cols == 0) {
    RemoveMatrix();
  } else if (cols_ != size_of_cols) {
    RemoveMatrix();
    CreateMatrix(temp.rows_, size_of_cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0;
           j < (size_of_cols < temp.cols_ ? size_of_cols : temp.cols_); j++) {
        matrix_[i][j] = temp.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows < 0 || cols < 0)
    throw std::invalid_argument("Argument is less than 1");
  if (rows == 0 || cols == 0)
    ReleaseMatrix();
  else {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double*[rows]();
    for (int i = 0; i < rows; ++i) {
      matrix_[i] = new double[cols]();
    }
  }
}
void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  ReleaseMatrix();
}
void S21Matrix::SetMatrix(double begin, double range) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = begin;
      begin += range;
    }
  }
}
void S21Matrix::CutMatrix(S21Matrix& dest, int row, int col) {
  int t;
  int s = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i != row) {
      t = 0;
      for (int j = 0; j < rows_; ++j) {
        if (j != col) {
          dest.matrix_[s][t] = matrix_[i][j];
          t++;
        }
      }
      s++;
    }
  }
}
void S21Matrix::CopyMatrix(const S21Matrix& dest) {
  if (matrix_ == nullptr || dest.matrix_ == nullptr) {
    throw std::invalid_argument("Matrix is not initialized");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = dest.matrix_[i][j];
    }
  }
}
bool S21Matrix::CheckForSameSize(const S21Matrix& first) {
  return first.cols_ == cols_ && first.rows_ == rows_;
}
void S21Matrix::ReleaseMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
bool S21Matrix::CheckSquare() { return cols_ == rows_; }
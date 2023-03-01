#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) { create_matrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Error. Rows or Cols must be more then zero.");
  }
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) : matrix_(nullptr) {
  *this = other;
}

S21Matrix::S21Matrix(S21Matrix&& other) { *this = std::move(other); }

S21Matrix::~S21Matrix() { delete_matrix(); }

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    for (int i = 0; i < std::min(rows, rows_); i++) {
      for (int j = 0; j < cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    delete_matrix();
    *this = temp;
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < std::min(cols, cols_); j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    delete_matrix();
    *this = temp;
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other && !(matrix_ && rows_ == other.rows_ &&
                          cols_ == other.cols_ && this->EqMatrix(other))) {
    delete_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    create_matrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other && !(matrix_ && rows_ == other.rows_ &&
                          cols_ == other.cols_ && this->EqMatrix(other))) {
    delete_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double x) const {
  S21Matrix res(*this);
  res.MulNumber(x);
  return res;
}

S21Matrix operator*(const double x, const S21Matrix& other) {
  S21Matrix res(other);
  res.MulNumber(x);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double x) {
  this->MulNumber(x);
  return *this;
}

double& S21Matrix::operator()(const int row, const int col) {
  if (row > rows_ || col > cols_) {
    throw std::invalid_argument("Error. Does not exist row or col.");
  }
  return matrix_[row][col];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Error. Matrix sizes must be the same.");
  }
  bool res = true;
  if (this != &other) {
    for (int i = 0; i < rows_ && res; ++i) {
      for (int j = 0; j < cols_ && res; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kEPS) {
          res = false;
        }
      }
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Error. Matrix sizes must be the same.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Error. Matrix sizes must be the same.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (std::isnan(num) || std::isinf(num)) {
    throw std::invalid_argument("Error: argument is NAN or INF");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Error. Cols and rows sizes must be the same.");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return temp;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_ || rows_ < 2) {
    throw std::invalid_argument(
        "Rows and cols must be the same and more the one");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] =
          reduce_matrix(i, j).Determinant() * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Rows and cols must be the same");
  }
  double res = 0;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix temp(rows_ - 1, cols_ - 1);
    for (int j = 0; j < rows_; j++) {
      res += matrix_[0][j] * reduce_matrix(0, j).Determinant() *
             ((0 + j) % 2 == 0 ? 1 : -1);
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Rows and cols must be the same");
  }
  double determ = Determinant();
  if (abs(determ) < kEPS) {
    throw std::invalid_argument("Determinant must be more then zero");
  }

  S21Matrix temp(rows_, cols_);
  if (rows_ == 1) {
    temp(0, 0) = 1 / matrix_[0][0];
  } else {
    temp = this->CalcComplements().Transpose();
    temp.MulNumber(1 / determ);
  }
  return temp;
}

void S21Matrix::create_matrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::delete_matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    rows_ = 0;
    cols_ = 0;
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix S21Matrix::reduce_matrix(const int x, const int y) const {
  S21Matrix temp(rows_ - 1, cols_ - 1);
  for (int i = 0, k = 0; i < temp.rows_; i++, k++) {
    if (k == x) k++;
    for (int j = 0, l = 0; j < temp.cols_; j++, l++) {
      if (l == y) l++;
      temp.matrix_[i][j] = matrix_[k][l];
    }
  }
  return temp;
}

// void S21Matrix::print_matrix() {
//   std::cout << "ROWS = " << rows_ << "\n"
//             << "COLS = " << cols_ << "\n";
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       if (j) std::cout << " ";
//       std::cout << matrix_[i][j];
//     }
//     std::cout << "\n";
//   }
// }

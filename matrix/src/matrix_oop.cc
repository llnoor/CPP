#include "matrix_oop.h"

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) throw std::logic_error("The invalid matrix");
  rows_ = rows;
  cols_ = cols;
  NewMatrix();
}

Matrix::Matrix(const Matrix& second)
    : rows_(second.rows_), cols_(second.cols_) {
  if (this != &second) {
    CopyMatrix(second);
  }
}

Matrix::Matrix(Matrix&& second) {
  if (this != &second) {
    rows_ = std::exchange(second.rows_, 0);
    cols_ = std::exchange(second.cols_, 0);
    matrix_ = std::exchange(second.matrix_, nullptr);
  }
}

int Matrix::get_rows() const noexcept { return rows_; }

int Matrix::get_cols() const noexcept { return cols_; }

void Matrix::set_rows(int update_rows) {
  if (update_rows < 1) {
    throw std::logic_error("Rows cannot be negative!");
  }
  Matrix second(update_rows, cols_);
  int rows = rows_ < update_rows ? rows_ : update_rows;
  UpdateMatrix(second, rows, cols_);
  *this = std::move(second);
}

void Matrix::set_cols(int update_cols) {
  if (update_cols < 1) {
    throw std::logic_error("Cols cannot be negative!");
  }
  Matrix second(rows_, update_cols);
  int cols = cols_ < update_cols ? cols_ : update_cols;
  UpdateMatrix(second, rows_, cols);
  *this = std::move(second);
}

Matrix& Matrix::operator=(const Matrix& second) {
  if (this != &second) {
    DeleteMatrix();
    rows_ = second.rows_;
    cols_ = second.cols_;
    CopyMatrix(second);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& second) {
  if (this != &second) {
    DeleteMatrix();
    std::swap(cols_, second.cols_);
    std::swap(rows_, second.rows_);
    std::swap(matrix_, second.matrix_);
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& second) {
  Matrix result(*this);
  result.MulMatrix(second);
  return result;
}

Matrix Matrix::operator*(const double number) {
  Matrix result(*this);
  result.MulNumber(number);
  return result;
}

// friend
Matrix operator*(double number, const Matrix& second) {
  Matrix result(second);
  result.MulNumber(number);
  return result;
}

// friend
Matrix operator*(const Matrix& second, double number) {
  Matrix result(second);
  result.MulNumber(number);
  return result;
}

Matrix Matrix::operator*=(const Matrix& second) {
  this->MulMatrix(second);
  return *this;
}

Matrix Matrix::operator*=(const double number) {
  this->MulNumber(number);
  return *this;
}

Matrix Matrix::operator+(const Matrix& second) {
  Matrix result(*this);
  result.SumMatrix(second);
  return result;
}

Matrix Matrix::operator-(const Matrix& second) {
  Matrix result(*this);
  result.SubMatrix(second);
  return result;
}

bool Matrix::operator==(const Matrix& second) { return EqMatrix(second); }

Matrix Matrix::operator+=(const Matrix& second) {
  SumMatrix(second);
  return *this;
}

Matrix Matrix::operator-=(const Matrix& second) {
  SubMatrix(second);
  return *this;
}

void Matrix::SumMatrix(const Matrix& second) {
  CheckMatrix(*this);
  CheckMatrix(second);
  if (rows_ != second.rows_ || cols_ != second.cols_)
    throw std::logic_error("Matrix dimensions must match!");
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[x][y] += second.matrix_[x][y];
    }
  }
}

void Matrix::SubMatrix(const Matrix& second) {
  CheckMatrix(*this);
  CheckMatrix(second);
  if (rows_ != second.rows_ || cols_ != second.cols_)
    throw std::logic_error("Matrix dimensions must match!");
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[x][y] -= second.matrix_[x][y];
    }
  }
}

void Matrix::MulMatrix(const Matrix& second) {
  // (A = m × k) (B = k × n) C = m × n = A × B
  // m = rows_
  // k = cols_ = second.rows_
  // n = second.cols_
  CheckMatrix(*this);
  CheckMatrix(second);
  if (cols_ != second.rows_)
    throw std::logic_error("First.cols_ & second.rows_ must match!");
  Matrix third = Matrix(rows_, second.cols_);
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < second.cols_; y++) {
      third(x, y) = 0;
      for (int z = 0; z < cols_; z += 1) {
        third.matrix_[x][y] =
            third.matrix_[x][y] + matrix_[x][z] * second.matrix_[z][y];
      }
    }
  }
  *this = third;
}

void Matrix::MulNumber(const double number) const {
  CheckMatrix(*this);
  if (number == NAN || number == INFINITY) {
    throw std::logic_error("This must be a number!");
  }

  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[x][y] *= number;
    }
  }
}

bool Matrix::EqMatrix(const Matrix& second) {
  CheckMatrix(*this);
  CheckMatrix(second);
  bool flag = true;
  if (rows_ != second.rows_ || cols_ != second.cols_) {
    flag = false;
  } else {
    for (int x = 0; x < rows_; x++) {
      for (int y = 0; y < cols_; y++) {
        if (fabs(matrix_[x][y] - second.matrix_[x][y]) > 1.0e-7) {
          flag = false;
          break;
        }
      }
    }
  }
  return flag;
}

Matrix Matrix::Transpose() const {
  CheckMatrix(*this);
  Matrix third(cols_, rows_);
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      third.matrix_[y][x] = matrix_[x][y];
      // third.matrix_[x][y] = matrix_[y][x];
    }
  }
  return third;
}

double Matrix::Determinant() const {
  CheckMatrix(*this);
  if (rows_ != cols_) throw std::length_error("The matrix must be square!");
  double result = 0;
  int sign = 1;
  switch (rows_) {
    case 0:
      break;
    case 1:
      result = matrix_[0][0];
      break;
    case 2:
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
      break;
    default:
      Matrix minor(this->get_rows() - 1, this->get_cols() - 1);
      for (int y = 0; y < cols_; y++) {
        CreatMinor(minor, 0, y);
        result = result + sign * matrix_[0][y] * minor.Determinant();
        sign = sign * -1;
      }
      minor.DeleteMatrix();
      break;
  }
  return result;
}

void Matrix::CreatMinor(Matrix& minor, int rows, int columns) const {
  int minor_x = 0;
  for (int x = 0; x < minor.get_rows(); x++) {
    if (x == rows) minor_x = 1;
    int minor_y = 0;
    for (int y = 0; y < minor.get_cols(); y++) {
      if (y == columns) minor_y = 1;
      minor.matrix_[x][y] = matrix_[x + minor_x][y + minor_y];
    }
  }
}

Matrix Matrix::CalcComplements() const {
  CheckMatrix(*this);
  if (rows_ != cols_) throw std::length_error("The matrix must be square!");
  int sign = 1;
  Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    Matrix minor(this->get_rows() - 1, this->get_cols() - 1);
    for (int x = 0; x < rows_; x += 1) {
      for (int y = 0; y < cols_; y += 1) {
        CreatMinor(minor, x, y);
        if (0 == (x + y) % 2) {
          sign = 1;
        } else {
          sign = -1;
        }
        result.matrix_[x][y] = sign * minor.Determinant();
      }
    }
    minor.DeleteMatrix();
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  CheckMatrix(*this);
  if (rows_ != cols_) throw std::length_error("The matrix must be square!");
  double determinant = Determinant();
  if (fabs(determinant) < 1.0e-7)
    throw std::logic_error("The determinant must not be zero");
  Matrix result(this->get_rows(), this->get_cols());
  if (cols_ == 1) {
    result.matrix_[0][0] = 1.0 / (matrix_[0][0]);
  } else {
    Matrix complements = this->CalcComplements();
    result = complements.Transpose();
    result.MulNumber(1.0 / determinant);
    complements.DeleteMatrix();
  }

  return result;
}

double& Matrix::operator()(int x, int y) {
  if (x >= rows_ || y >= cols_ || x < 0 || y < 0)
    throw std::logic_error("Index is incorrect");
  return matrix_[x][y];
}

void Matrix::NewMatrix() {
  matrix_ = new double*[rows_];
  for (int x = 0; x < rows_; x++) {
    matrix_[x] = new double[cols_]();
  }
}

void Matrix::CheckMatrix(const Matrix& second) const {
  if (second.matrix_ == nullptr || second.cols_ <= 0 || second.rows_ <= 0)
    throw std::length_error("Empty matrix");
}

void Matrix::CopyMatrix(const Matrix& second) {
  NewMatrix();
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[x][y] = second.matrix_[x][y];
    }
  }
}

void Matrix::UpdateMatrix(Matrix& second, int rows, int cols) {
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < cols; y++) {
      second.matrix_[x][y] = matrix_[x][y];
    }
  }
}

void Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int x = 0; x < rows_; x++) {
      if (matrix_[x] != nullptr) delete[] matrix_[x];
    }
    delete[] matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix_ = nullptr;
  }
}

Matrix::~Matrix() {
  DeleteMatrix();
  rows_ = 0;
  cols_ = 0;
}

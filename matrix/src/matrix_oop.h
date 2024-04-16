#ifndef MATRIX_OOP
#define MATRIX_OOP

#include <math.h>

#include <iostream>
#include <utility>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void NewMatrix();
  void CopyMatrix(const Matrix& second);
  void UpdateMatrix(Matrix& second, int rows, int cols);
  void DeleteMatrix();
  void CheckMatrix(const Matrix& second) const;

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& second);
  Matrix(Matrix&& second);
  ~Matrix();

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(int update_rows);
  void set_cols(int update_cols);

  bool operator==(const Matrix& second);
  Matrix& operator=(Matrix&& second);
  Matrix& operator=(const Matrix& second);
  Matrix operator+(const Matrix& second);
  Matrix operator-(const Matrix& second);
  Matrix operator+=(const Matrix& second);
  Matrix operator-=(const Matrix& second);
  Matrix operator*=(const Matrix& second);
  Matrix operator*=(const double number);
  Matrix operator*(const Matrix& second);
  Matrix operator*(const double number);
  friend Matrix operator*(double, const Matrix&);
  friend Matrix operator*(const Matrix&, double);
  double& operator()(int x, int y);

  void SumMatrix(const Matrix& second);
  void SubMatrix(const Matrix& second);
  void MulMatrix(const Matrix& second);
  void MulNumber(const double number) const;
  bool EqMatrix(const Matrix& second);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  void CreatMinor(Matrix& minor, int rows, int columns) const;
  Matrix InverseMatrix() const;
};

#endif  // MATRIX_OOP

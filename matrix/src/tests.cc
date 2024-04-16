
#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Conctructor, c10) {
  Matrix matrix;
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
}

TEST(Conctructor, c11) {
  Matrix matrix(5, 4);
  EXPECT_EQ(matrix.get_rows(), 5);
  EXPECT_EQ(matrix.get_cols(), 4);
}

TEST(Conctructor, copy) {
  Matrix matrix(5, 4);
  Matrix second_matrix(matrix);
  EXPECT_EQ(second_matrix.get_rows(), 5);
  EXPECT_EQ(second_matrix.get_cols(), 4);
  EXPECT_EQ(matrix == second_matrix, true);
}

TEST(Conctructor, move) {
  Matrix matrix(5, 4);
  Matrix second_matrix(std::move(matrix));
  EXPECT_EQ(second_matrix.get_rows(), 5);
  EXPECT_EQ(second_matrix.get_cols(), 4);
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
}

TEST(Conctructor, moveGet) {
  Matrix matrix(5, 5);
  for (int i = 0; i < matrix.get_rows(); i++) {
    for (int j = 0; j < matrix.get_cols(); j++) {
      matrix(i, j) = 1;
    }
  }
  Matrix matrixMove;
  matrixMove = std::move(matrix);
  EXPECT_EQ(matrixMove.get_rows(), 5);
  EXPECT_EQ(matrixMove.get_cols(), 5);
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
}

TEST(Sum, sum1) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 3;
      second(i, j) = 2;
    }
  }
  first.SumMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 5);
    }
  }
}

TEST(Sum, sum3) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 2;
    }
  }
  first.SumMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 2);
    }
  }
}

TEST(Sub, sub1) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 4;
    }
  }
  first.SubMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), -3);
    }
  }
}

TEST(Sub, sub3) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
    }
  }
  first.SubMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 1);
    }
  }
}

TEST(Eq, eq1) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 1;
    }
  }
  EXPECT_EQ(first.EqMatrix(second), true);
}

TEST(Eq, eq2) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 2;
    }
  }
  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(Eq, eq3) {
  Matrix first(3, 3);
  Matrix second(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      second(i, j) = 1;
    }
  }
  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(MulNumber, mulNumber1) {
  Matrix first(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 2;
    }
  }
  first.MulNumber(2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 4);
    }
  }
}

TEST(MulMatrix, mulMatrix1) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 2;
      second(i, j) = 4;
    }
  }
  first.MulMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 24);
    }
  }
}
TEST(MulMatrix, mulMatrix2) {
  Matrix first(3, 4);
  Matrix second(4, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      first(i, j) = 2;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      second(i, j) = 4;
    }
  }
  first.MulMatrix(second);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 32);
    }
  }
  EXPECT_EQ(first.get_cols(), 3);
  EXPECT_EQ(first.get_rows(), 3);
}

TEST(Transpose, transpose1) {
  Matrix first(3, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  first(2, 0) = 8;
  first(2, 1) = 9;

  Matrix second = first.Transpose();
  EXPECT_DOUBLE_EQ(second.get_rows(), 2);
  EXPECT_DOUBLE_EQ(second.get_cols(), 3);
  EXPECT_DOUBLE_EQ(second(0, 0), 1);
  EXPECT_DOUBLE_EQ(second(0, 1), 3);
  EXPECT_DOUBLE_EQ(second(0, 2), 8);
  EXPECT_DOUBLE_EQ(second(1, 0), 2);
  EXPECT_DOUBLE_EQ(second(1, 1), 4);
  EXPECT_DOUBLE_EQ(second(1, 2), 9);
}

TEST(Determinant, determinant2) {
  Matrix first(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = count;
      count++;
    }
  }
  EXPECT_DOUBLE_EQ(first.Determinant(), 0);
}

TEST(Determinant, determinant3) {
  Matrix first(4, 4);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(0, 2) = 3;
  first(0, 3) = 4;

  first(1, 0) = 1;
  first(1, 1) = 2;
  first(1, 2) = 5;
  first(1, 3) = 7;

  first(2, 0) = 1;
  first(2, 1) = 0;
  first(2, 2) = 6;
  first(2, 3) = 8;

  first(3, 0) = 1;
  first(3, 1) = 0;
  first(3, 2) = 6;
  first(3, 3) = 6;
  EXPECT_EQ(first.Determinant(), -8);
}

TEST(Determinant, determinant4) {
  Matrix first(1, 1);
  first(0, 0) = 2.0;
  EXPECT_EQ(first.Determinant(), 2);
}

TEST(CalcComplements, calcComplements1) {
  Matrix first(3, 3);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(0, 2) = 3;

  first(1, 0) = 0;
  first(1, 1) = 4;
  first(1, 2) = 2;

  first(2, 0) = 5;
  first(2, 1) = 2;
  first(2, 2) = 1;

  first = first.CalcComplements();

  EXPECT_EQ(first(0, 0), 0);
  EXPECT_EQ(first(0, 1), 10);
  EXPECT_EQ(first(0, 2), -20);
  EXPECT_EQ(first(1, 0), 4);
  EXPECT_EQ(first(1, 1), -14);
  EXPECT_EQ(first(1, 2), 8);
  EXPECT_EQ(first(2, 0), -8);
  EXPECT_EQ(first(2, 1), -2);
  EXPECT_EQ(first(2, 2), 4);
}

TEST(CalcComplements, calcComplements3) {
  Matrix first(1, 1);
  first(0, 0) = 2.0;
  Matrix second = first.CalcComplements();
  EXPECT_EQ(second(0, 0), 2);
}

TEST(InverseMatrix, inverse2) {
  Matrix first(3, 3);
  first(0, 0) = 2.0;
  first(0, 1) = 5.0;
  first(0, 2) = 7.0;
  first(1, 0) = 6.0;
  first(1, 1) = 3.0;
  first(1, 2) = 4.0;
  first(2, 0) = 5.0;
  first(2, 1) = -2.0;
  first(2, 2) = -3.0;

  Matrix matrix_res(3, 3);
  matrix_res(0, 0) = 1.0;
  matrix_res(0, 1) = -1.0;
  matrix_res(0, 2) = 1.0;
  matrix_res(1, 0) = -38.0;
  matrix_res(1, 1) = 41.0;
  matrix_res(1, 2) = -34.0;
  matrix_res(2, 0) = 27.0;
  matrix_res(2, 1) = -29.0;
  matrix_res(2, 2) = 24.0;

  Matrix second = first.InverseMatrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(second(i, j), matrix_res(i, j));
    }
  }
}

TEST(InverseMatrix, inverse3) {
  Matrix first(1, 1);
  first(0, 0) = 2.0;
  Matrix second = first.InverseMatrix();
  EXPECT_EQ(second(0, 0), 0.5);
}

TEST(Overloading, a1) {
  Matrix first(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = count;
      count++;
    }
  }
  Matrix second = first;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(first(i, j), second(i, j));
    }
  }
}

TEST(Overloading, sum1) {
  Matrix first(3, 3);
  Matrix second(3, 3);
  Matrix third(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 2;
      // third(i, j) = 3;
    }
  }
  third = first + second;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(third(i, j), 3);
    }
  }
}

TEST(Overloading, sum3) {
  Matrix first(2, 2);
  Matrix second(2, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      first(i, j) = 1;
      second(i, j) = 4;
    }
  }
  first += second;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 5);
    }
  }
}

TEST(Overloading, sub1) {
  Matrix first(3, 3);
  Matrix second(3, 3);
  Matrix third(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 2;
      // third(i, j) = 3;
    }
  }
  third = first - second;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(third(i, j), -1);
    }
  }
}

TEST(Overloading, mult2) {
  Matrix first(3, 3);
  Matrix second(3, 3);
  Matrix third(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 3;
    }
  }
  second = first * 2;
  third = 2 * first;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(second(i, j), 6);
      EXPECT_DOUBLE_EQ(third(i, j), 6);
    }
  }
}

TEST(Overloading, mult4) {
  Matrix first(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 3;
    }
  }
  first *= 2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 6);
    }
  }
}

TEST(Overloading, eq) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix third(2, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      first(i, j) = 11;
    }
  }
  second = third = first;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 11);
      EXPECT_DOUBLE_EQ(second(i, j), 11);
      EXPECT_DOUBLE_EQ(third(i, j), 11);
    }
  }
}

TEST(Overloading, eq1) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 7;
      second(i, j) = 7;
    }
  }
  EXPECT_EQ(first == second, true);
}

TEST(Overloading, eq2) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 7;
      second(i, j) = 2;
    }
  }
  EXPECT_EQ(first == second, false);
}

/////// EXPECT_ANY_THROW //////

TEST(Conctructor, negativeRows) { EXPECT_ANY_THROW(Matrix matrix(-3, 4)); }

TEST(Conctructor, c1) {
  Matrix matrix;
  EXPECT_ANY_THROW(matrix(4, 4));
}

TEST(Sum, sum2) {
  Matrix first(1, 1);
  Matrix second(3, 3);
  first(0, 0) = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      second(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(first.SumMatrix(second));
}

TEST(Sub, sub2) {
  Matrix first(3, 3);
  Matrix second(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      second(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(first.SubMatrix(second));
}

TEST(MulNumber, mulNumber2) {
  double inf = INFINITY;
  Matrix first(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(first.MulNumber(inf));
}

TEST(MulNumber, mulNumber3) {
  Matrix matrix0 = Matrix();
  EXPECT_ANY_THROW(matrix0.MulNumber(2));
}

TEST(MulMatrix, mulMatrix3) {
  Matrix first(3, 3);
  Matrix second(4, 4);

  EXPECT_ANY_THROW(first.MulMatrix(second));
}

TEST(Transpose, transpose2) {
  Matrix first;
  EXPECT_ANY_THROW(first.Transpose());
}

TEST(Determinant, determinant1) {
  Matrix first(3, 4);
  EXPECT_ANY_THROW(first.Determinant());
}

TEST(CalcComplements, calcComplements2) {
  Matrix first(4, 5);
  EXPECT_ANY_THROW(first.CalcComplements());
}

TEST(InverseMatrix, inverse1) {
  Matrix first(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = count;
      count++;
    }
  }
  EXPECT_ANY_THROW(first.InverseMatrix());
}

TEST(Setter, set1) {
  Matrix matrix(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix(i, j) = 1;
    }
  }
  matrix.set_cols(4);
  matrix.set_rows(4);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1);
  EXPECT_DOUBLE_EQ(matrix(3, 3), 0);
  EXPECT_ANY_THROW(matrix.set_cols(-4));
}

TEST(Setter, set2) {
  Matrix matrix(3, 3);
  EXPECT_ANY_THROW(matrix.set_rows(-4));
}

TEST(Overloading, sum2) {
  Matrix first(3, 3);
  Matrix second(3, 4);
  Matrix third(3, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(third = first + second);
}

TEST(Overloading, sum4) {
  Matrix first(3, 3);
  Matrix second(4, 4);

  EXPECT_ANY_THROW(first += second);
}

TEST(Overloading, sub2) {
  Matrix first(3, 3);
  Matrix second(3, 4);
  Matrix third(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(third = first - second);
}

TEST(Overloading, sub3) {
  Matrix first(3, 3);
  Matrix second(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 1;
      second(i, j) = 4;
    }
  }
  first -= second;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), -3);
    }
  }
}

TEST(Overloading, sub4) {
  Matrix first(3, 3);
  Matrix second(4, 4);

  EXPECT_ANY_THROW(first -= second);
}

TEST(Overloading, mult1) {
  Matrix first(3, 3);
  Matrix second(3, 3);
  Matrix third(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 3;
      second(i, j) = 2;
      third(i, j) = 1;
    }
  }
  third = first * second;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(third(i, j), 18);
    }
  }
  Matrix first1(3, 3);
  Matrix second2(4, 4);
  EXPECT_ANY_THROW(third = first1 * second2);
}

TEST(Overloading, mult3) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      first(i, j) = 3;
      second(i, j) = 7;
    }
  }
  first *= second;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), 63);
    }
  }
  Matrix first1(1, 1);
  Matrix second2(2, 2);
  EXPECT_ANY_THROW(first1 *= second2);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

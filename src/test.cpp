#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(create_matrix, test1) {
  ASSERT_ANY_THROW(S21Matrix src(1, 0));
  ASSERT_ANY_THROW(S21Matrix src(0, 1));
  ASSERT_ANY_THROW(S21Matrix src(1, -1));
  ASSERT_ANY_THROW(S21Matrix src(-1, 1));
}

TEST(create_matrix, test2) {
  S21Matrix src(S21Matrix(5, 5));
  ASSERT_EQ(src.GetCols(), 5);
  ASSERT_EQ(src.GetRows(), 5);

  S21Matrix src1{S21Matrix(3, 3)};
  ASSERT_EQ(src1.GetCols(), 3);
  ASSERT_EQ(src1.GetRows(), 3);
}

TEST(create_matrix, test3) {
  S21Matrix src;
  ASSERT_EQ(src.GetRows(), 1);
  ASSERT_EQ(src.GetCols(), 1);

  S21Matrix src1 = S21Matrix(3, 2);
  ASSERT_EQ(src1.GetRows(), 3);
  ASSERT_EQ(src1.GetCols(), 2);
}

TEST(create_matrix, test4) {
  S21Matrix src(3, 3);
  ASSERT_DOUBLE_EQ(src(0, 0), 0);
}

TEST(set_matrix, test1) {
  S21Matrix src{};
  src.SetRows(2);
  src.SetCols(3);
  ASSERT_EQ(src.GetRows(), 2);
  ASSERT_EQ(src.GetCols(), 3);
  ASSERT_ANY_THROW(src.SetCols(-1));
  ASSERT_ANY_THROW(src.SetRows(-1));
}

TEST(set_matrix, test2) {
  S21Matrix src(2, 2);
  src(0, 0) = 2;
  src(0, 1) = 2;
  src(1, 0) = 2;
  src(1, 1) = 2;
  ASSERT_DOUBLE_EQ(src(0, 0), 2);

  src.SetRows(3);
  ASSERT_DOUBLE_EQ(src(2, 0), 0);
  ASSERT_DOUBLE_EQ(src(2, 1), 0);
  ASSERT_EQ(src.GetRows(), 3);
  ASSERT_EQ(src.GetCols(), 2);
}

TEST(set_matrix, test3) {
  S21Matrix src(5, 5);
  src.SetRows(2);
  ASSERT_ANY_THROW(src(4, 0));

  src.SetCols(1);
  ASSERT_ANY_THROW(src(1, 2));
}

TEST(set_matrix, test4) {
  S21Matrix a(3, 3), b(1, 1);
  a(0, 0) = 1;
  b(0, 0) = 1;
  a.SetCols(1);
  a.SetRows(1);

  ASSERT_DOUBLE_EQ(a.GetRows(), 1);
  ASSERT_DOUBLE_EQ(a.GetCols(), 1);

  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 1; j++) {
      ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
    }
  }
}

TEST(eq_matrix, test1) {
  S21Matrix src(2, 3);
  S21Matrix src1(5, 6);
  src1(4, 5) = 10.5;
  src1(3, 4) = 8.1;
  src = src1;
  ASSERT_EQ(src.GetRows(), 5);
  ASSERT_EQ(src.GetCols(), 6);
  ASSERT_DOUBLE_EQ(src(4, 5), 10.5);
  ASSERT_DOUBLE_EQ(src(3, 4), 8.1);
}

TEST(eq_matrix, test2) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 12;
  a(1, 0) = -25;
  a(1, 1) = -100;

  S21Matrix b(2, 2);
  b(0, 0) = 5;
  b(0, 1) = 12;
  b(1, 0) = -25;
  b(1, 1) = -100;

  ASSERT_TRUE(a == b);
  ASSERT_TRUE(a.EqMatrix(b));

  a(0, 0) = 0;
  ASSERT_FALSE(a == b);
  ASSERT_FALSE(a.EqMatrix(b));

  a.SetRows(1);
  ASSERT_ANY_THROW(a == b);
  ASSERT_ANY_THROW(a.EqMatrix(b));
}

TEST(sum_matrix, test1) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 12;
  a(1, 0) = -25;
  a(1, 1) = -100;

  S21Matrix b(2, 2);
  b(1, 0) = 8;
  b(1, 1) = 16;

  S21Matrix c = a + b;
  ASSERT_DOUBLE_EQ(c(0, 0), 5);
  ASSERT_DOUBLE_EQ(c(0, 1), 12);
  ASSERT_DOUBLE_EQ(c(1, 0), -17);
  ASSERT_DOUBLE_EQ(c(1, 1), -84);

  S21Matrix d = b + a;
  ASSERT_DOUBLE_EQ(c(0, 0), d(0, 0));
  ASSERT_DOUBLE_EQ(c(0, 1), d(0, 1));
  ASSERT_DOUBLE_EQ(c(1, 0), d(1, 0));
  ASSERT_DOUBLE_EQ(c(1, 1), d(1, 1));

  a += a;
  ASSERT_DOUBLE_EQ(a(0, 0), 10);
  ASSERT_DOUBLE_EQ(a(0, 1), 24);
  ASSERT_DOUBLE_EQ(a(1, 0), -50);
  ASSERT_DOUBLE_EQ(a(1, 1), -200);

  b.SumMatrix(a);
  ASSERT_DOUBLE_EQ(b(0, 0), 10);
  ASSERT_DOUBLE_EQ(b(0, 1), 24);
  ASSERT_DOUBLE_EQ(b(1, 0), -42);
  ASSERT_DOUBLE_EQ(b(1, 1), -184);
}

TEST(sum_matrix, test2) {
  S21Matrix a(1, 1);
  S21Matrix b(2, 2);

  ASSERT_ANY_THROW(a + b);
  ASSERT_ANY_THROW(b + a);
}

TEST(sub_matrix, test1) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 12;
  a(1, 0) = -25;
  a(1, 1) = -100;

  S21Matrix b(2, 2);
  b(1, 0) = 8;
  b(1, 1) = 16;

  S21Matrix c = a - b;
  ASSERT_DOUBLE_EQ(c(0, 0), 5);
  ASSERT_DOUBLE_EQ(c(0, 1), 12);
  ASSERT_DOUBLE_EQ(c(1, 0), -33);
  ASSERT_DOUBLE_EQ(c(1, 1), -116);

  S21Matrix d = b - a;
  ASSERT_DOUBLE_EQ(-5, d(0, 0));
  ASSERT_DOUBLE_EQ(-12, d(0, 1));
  ASSERT_DOUBLE_EQ(33, d(1, 0));
  ASSERT_DOUBLE_EQ(116, d(1, 1));

  b.SubMatrix(a);
  ASSERT_DOUBLE_EQ(b(0, 0), -5);
  ASSERT_DOUBLE_EQ(d(0, 1), -12);
  ASSERT_DOUBLE_EQ(b(1, 0), 33);
  ASSERT_DOUBLE_EQ(b(1, 1), 116);

  b -= d;
  ASSERT_DOUBLE_EQ(b(0, 0), 0);
  ASSERT_DOUBLE_EQ(b(0, 1), 0);
  ASSERT_DOUBLE_EQ(b(1, 0), 0);
  ASSERT_DOUBLE_EQ(b(1, 1), 0);
}

TEST(sub_matrix, test2) {
  S21Matrix a(1, 1);
  S21Matrix b(2, 2);

  ASSERT_ANY_THROW(a - b);
  ASSERT_ANY_THROW(b - a);
  ASSERT_ANY_THROW(a.SubMatrix(b));
  ASSERT_ANY_THROW(b.SubMatrix(a));
}

TEST(mul_matrix, test1) {
  S21Matrix a;
  S21Matrix b(2, 2);
  ASSERT_ANY_THROW(a * b);
  ASSERT_ANY_THROW(a.MulMatrix(b));
}

TEST(mul_matrix, test2) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  S21Matrix b(1, 3);
  b(0, 0) = 0.5;
  b(0, 1) = 0.75;
  b(0, 2) = 5;

  S21Matrix c = a * b;

  ASSERT_DOUBLE_EQ(c(0, 0), 0.5);
  ASSERT_DOUBLE_EQ(c(0, 1), 0.75);
  ASSERT_DOUBLE_EQ(c(0, 2), 5);
  ASSERT_DOUBLE_EQ(c(1, 0), 1);
  ASSERT_DOUBLE_EQ(c(1, 1), 1.5);
  ASSERT_DOUBLE_EQ(c(1, 2), 10);
  ASSERT_DOUBLE_EQ(c(2, 0), 1.5);
  ASSERT_DOUBLE_EQ(c(2, 1), 2.25);
  ASSERT_DOUBLE_EQ(c(2, 2), 15);

  ASSERT_EQ(c.GetRows(), 3);
  ASSERT_EQ(c.GetCols(), 3);
}

TEST(mul_matrix, test3) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  S21Matrix b(1, 3);
  b(0, 0) = 0.5;
  b(0, 1) = 0.75;
  b(0, 2) = 5;

  S21Matrix c = b * a;

  ASSERT_DOUBLE_EQ(c(0, 0), 17);
  ASSERT_EQ(c.GetRows(), 1);
  ASSERT_EQ(c.GetCols(), 1);
}

TEST(mul_matrix, test4) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  S21Matrix b(1, 3);
  b(0, 0) = 0.5;
  b(0, 1) = 0.75;
  b(0, 2) = 5;

  b *= a;

  ASSERT_DOUBLE_EQ(b(0, 0), 17);
  ASSERT_EQ(b.GetRows(), 1);
  ASSERT_EQ(b.GetCols(), 1);
}

TEST(mul_number, test1) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  a = a * 10;
  ASSERT_DOUBLE_EQ(a(0, 0), 10);
  ASSERT_DOUBLE_EQ(a(1, 0), 20);
  ASSERT_DOUBLE_EQ(a(2, 0), 30);

  a *= 10;
  ASSERT_DOUBLE_EQ(a(0, 0), 100);
  ASSERT_DOUBLE_EQ(a(1, 0), 200);
  ASSERT_DOUBLE_EQ(a(2, 0), 300);

  a.MulNumber(0.1);
  ASSERT_DOUBLE_EQ(a(0, 0), 10);
  ASSERT_DOUBLE_EQ(a(1, 0), 20);
  ASSERT_DOUBLE_EQ(a(2, 0), 30);
}

TEST(mul_number, test2) {
  S21Matrix a;
  ASSERT_ANY_THROW(a * NAN);
  ASSERT_ANY_THROW(a *= NAN);
  ASSERT_ANY_THROW(a.MulNumber(NAN));

  ASSERT_ANY_THROW(a * INFINITY);
  ASSERT_ANY_THROW(a *= INFINITY);
  ASSERT_ANY_THROW(a.MulNumber(INFINITY));
}

TEST(mul_number, test3) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  a = 10 * a;
  ASSERT_DOUBLE_EQ(a(0, 0), 10);
  ASSERT_DOUBLE_EQ(a(1, 0), 20);
  ASSERT_DOUBLE_EQ(a(2, 0), 30);
}

TEST(mul_number, test4) {
  S21Matrix a;
  ASSERT_ANY_THROW(NAN * a);
  ASSERT_ANY_THROW(INFINITY * a);
}

TEST(transpose, test1) {
  S21Matrix a{1, 4};
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;

  S21Matrix b = a.Transpose();

  S21Matrix c{4, 1};
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  c(3, 0) = 4;
  ASSERT_TRUE(b == c);
}

TEST(transpose, test2) {
  S21Matrix a{2, 2};
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b = a.Transpose();

  S21Matrix c{2, 2};
  c(0, 0) = 1;
  c(0, 1) = 3;
  c(1, 0) = 2;
  c(1, 1) = 4;
  ASSERT_TRUE(b == c);
}

TEST(calc_complements, test1) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b = a.CalcComplements();
  ASSERT_DOUBLE_EQ(b(0, 0), 4);
  ASSERT_DOUBLE_EQ(b(0, 1), -3);
  ASSERT_DOUBLE_EQ(b(1, 0), -2);
  ASSERT_DOUBLE_EQ(b(1, 1), 1);
}

TEST(calc_complements, test2) {
  S21Matrix a{2, 3};
  ASSERT_ANY_THROW(a.CalcComplements());

  S21Matrix b{1, 1};
  ASSERT_ANY_THROW(b.CalcComplements());
}

TEST(s21_determinant_check, test1) {
  S21Matrix a(2, 3);
  ASSERT_ANY_THROW(a.Determinant());
}

TEST(s21_determinant_check, test2) {
  S21Matrix a(5, 5);

  a(0, 0) = 0;
  a(0, 1) = 12;
  a(0, 2) = -12;
  a(0, 3) = 12;
  a(0, 4) = 6;

  a(1, 0) = -3;
  a(1, 1) = -9;
  a(1, 2) = 9;
  a(1, 3) = 9;
  a(1, 4) = -6;

  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = -2;
  a(2, 3) = 4;
  a(2, 4) = -2;

  a(3, 0) = -3;
  a(3, 1) = -17;
  a(3, 2) = 13;
  a(3, 3) = 3;
  a(3, 4) = -8;

  a(4, 0) = 0;
  a(4, 1) = 0;
  a(4, 2) = 4;
  a(4, 3) = -8;
  a(4, 4) = 0;

  ASSERT_DOUBLE_EQ(a.Determinant(), -1728);
}

TEST(inverse_check, test1) {
  S21Matrix a(3, 3), b(3, 3);

  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;

  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = -38;
  b(1, 1) = 41;
  b(1, 2) = -34;
  b(2, 0) = 27;
  b(2, 1) = -29;
  b(2, 2) = 24;

  a = a.InverseMatrix();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
    }
  }
}

TEST(inverse_check, test2) {
  S21Matrix a(3, 3);

  a(0, 0) = 6;
  a(0, 1) = -1;
  a(0, 2) = 12;
  a(1, 0) = -3;
  a(1, 1) = -5;
  a(1, 2) = -6;
  a(2, 0) = 1;
  a(2, 1) = 4;
  a(2, 2) = 2;

  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(inverse_check, test3) {
  S21Matrix a(2, 3);
  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(inverse_check, test4) {
  S21Matrix b(1, 1), a(1, 1);
  a(0, 0) = 2;
  b(0, 0) = 0.5;

  a = a.InverseMatrix();
  ASSERT_DOUBLE_EQ(b(0, 0), a(0, 0));
}

TEST(inverse_check, test5) {
  S21Matrix a(1, 1), b(1, 1);

  ASSERT_ANY_THROW(a.InverseMatrix());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
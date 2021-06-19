/*!
* \file
* \brief Plik zawiera testy dotyczące wektorów 3D
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"
#include "../inc/matrix3x3.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Konstruktor bezparametryczny i parametryczny - tablica"){

  Matrix3x3 x;
  double Ty[SIZE][SIZE] = {{0,0,0},{0,0,0},{0,0,0}};
  Matrix3x3 y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor parametryczny - matrix3x3"){

  double Ty[SIZE][SIZE] = {{4,5,-2},{-7,0,1},{1,-5,0}};
  Matrix3x3 y(Ty);
  Matrix3x3 x(y);

  CHECK(x == y);
}

TEST_CASE("Dodawanie"){

  double Tx[SIZE][SIZE] = {{4,5,-2},{-7,0,1},{1,-5,0}};
  double Ty[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  double Tz[SIZE][SIZE] = {{-3,5,-1},{-3,5,-1},{2,-10,0}};

  Matrix3x3 x(Tx), y(Ty), z(Tz);

  CHECK(x + y == z);
}

TEST_CASE("Mnożenie matrix3x3 * vector3D"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  double Tv[SIZE] = {-1,1,2};
  double Tr[SIZE] = {9,-3,-6};

  Matrix3x3 x(Tx);
  Vector3D v(Tv), r(Tr);

  CHECK(r == x * v);
}

TEST_CASE("Mnożenie matrix3x3 * matrix3x3"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  double Ty[SIZE][SIZE] = {{1,-1,0},{2,0,1},{-1,-1,-1}};
  double Tz[SIZE][SIZE] = {{-8,6,-1},{16,-2,7},{-9,-1,-5}};

  Matrix3x3 x(Tx), y(Ty), z(Tz);

  CHECK(z == x * y);
}

TEST_CASE("Operator ()"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 x(Tx);

  CHECK(x(1, 0) == 4);
}

TEST_CASE("Operator () - wiersz poza zasięgiem na plus"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 x(Tx);

  WARN_THROWS(x(SIZE, 0));
}

TEST_CASE("Operator () - wiersz poza zasięgiem na minus"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 x(Tx);

  WARN_THROWS(x(-1, 0));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na plus"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 x(Tx);

  WARN_THROWS(x(1, SIZE));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na minus"){

  double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 x(Tx);

  WARN_THROWS(x(1, -1));
}

TEST_CASE("Porownanie - minimalnie nierowne"){
  
  double Tx[SIZE][SIZE] = {{1,1,1},{1,1,1},{1,1,1}};
  double Ty[SIZE][SIZE] = {{1,1},{1,1,1},{1,1,1.01}};

  Matrix3x3 x(Tx), y(Ty);

  CHECK(!(x == y));
}

TEST_CASE("Porownanie - minimalnie rowne"){
  
  double Tx[SIZE][SIZE] = {{1,1,1},{1,1,1},{1,1,1}};
  double Ty[SIZE][SIZE] = {{1,1,1},{1,1,1},{1,1,1.009}};

  Matrix3x3 x(Tx), y(Ty);

  CHECK(x == y);
}

TEST_CASE("Macierz jednostkowa - pusta macierz"){

  double Ti[SIZE][SIZE] = {{1,0,0},{0,1,0},{0,0,1}};
  Matrix3x3 i(Ti), x;

  x.IdentityMatrix();

  CHECK(x == i);
}

TEST_CASE("Macierz jednostkowa - niepusta macierz"){

  double Ti[SIZE][SIZE] = {{1,0,0},{0,1,0},{0,0,1}};
    double Tx[SIZE][SIZE] = {{-7,0,1},{4,5,-2},{1,-5,0}};
  Matrix3x3 i(Ti), x(Tx);

  x.IdentityMatrix();

  CHECK(x == i); 
}

TEST_CASE("Macierz obrotu 90 stopni oś z"){

  double Tx[SIZE][SIZE] = {{0,-1,0},{1,0,0},{0,0,1}};
  Matrix3x3 i, x(Tx);
  
  i.IdentityMatrix();
  i.RotationMatrix(90);

  CHECK(i == x); 
}

TEST_CASE("Wyświetlanie"){

  double Tx[SIZE][SIZE] = {{5,2,3},{1,0,1},{-2,3,-5}};
  Matrix3x3 x(Tx);

  std::stringstream out;

  out << x;

  CHECK("| 5.0000000000 | | 2.0000000000 | | 3.0000000000 | \n| 1.0000000000 | | 0.0000000000 | | 1.0000000000 | \n| -2.0000000000 | | 3.0000000000 | | -5.0000000000 | \n" == out.str());
}

TEST_CASE("Wczytywanie"){

  std::stringstream in("2 \n 3 \n 0.77 \n 0 \n -3 \n 1 \n 0.5 \n 1 \n 2");
  double Ty[SIZE][SIZE] = {{2,3,0.77}, {0,-3,1}, {0.5,1,2}};
  Matrix3x3 x, y(Ty);

  in >> x;

  CHECK(x == y);
}



/*!
* \file
* \brief Plik zawiera testy dotyczące wektorów 3D
*/

#include "../tests/doctest/doctest.h"
#include "../inc/vector3D.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Zliczanie wszystkich wektorów"){

  Vector3D::ClearAllNumVectors();
  double Tx[SIZE] = {5,2, 3};
  Vector3D x(Tx), y;
  Vector3D z;

  int i = Vector3D::ReturnAllNumVectors();
  CHECK(i == 3);
}

TEST_CASE("Zliczanie aktywnych wektorów"){

  double Tx[SIZE] = {5,2, 3};
  Vector3D x(Tx), y;
  Vector3D z;

  int i = Vector3D::ReturnActiveNumVectors();
  CHECK(i == 3) ;
}

TEST_CASE("Zliczanie wszystkich wektorów"){
    
  int i = Vector3D::ReturnAllNumVectors();
  CHECK(i == 6);
}

TEST_CASE("Konstruktor bezparametryczny i parametryczny - tablica"){

  Vector3D x;
  double Ty[SIZE] = {0,0,0};
  Vector3D y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor kopiujący"){

  double Ty[SIZE] = {4,5,-2};
  Vector3D y(Ty);
  Vector3D x(y);

  CHECK(x == y);
}


TEST_CASE("Dodawanie"){

  double Tx[SIZE] = {1,2,3};
  double Ty[SIZE] = {2,0,-4};
  double Tz[SIZE] = {3,2,-1};

  Vector3D x(Tx), y(Ty), z(Tz);

  CHECK(x + y == z);
}

TEST_CASE("Odejmowanie"){

  double Tx[SIZE] = {1,2,3};
  double Ty[SIZE] = {2,0,-4};
  double Tz[SIZE] = {-1,2,7};

  Vector3D x(Tx), y(Ty), z(Tz);

  CHECK(x - y == z);  
}

TEST_CASE("Mnożenie vector3D * double"){

  double Tx[SIZE] = {1,2,-3};
  double Ty[SIZE] = {2,4,-6};

  Vector3D x(Tx), y(Ty);

  CHECK(x * 2.0 == y);
}

TEST_CASE("Mnożenie vector3D * vector3D"){

  double Tx[SIZE] = {1,2,-3};
  double Ty[SIZE] = {2,4,-6};
  double Tz[SIZE] = {2, 8, 18};

  Vector3D x(Tx), y(Ty), z(Tz);

  CHECK(x * y == z); 
}

TEST_CASE("Dzielenie vector3D / double"){

  double Tx[SIZE] = {1,2,-3};
  double Ty[SIZE] = {0.5,1,-1.5};

  Vector3D x(Tx), y(Ty);

  CHECK(x / 2.0 == y);
}

TEST_CASE("Operator []"){

  double Tx[SIZE] = {-2,0,1};
  Vector3D x(Tx);

  CHECK( x[0] == -2);
}

TEST_CASE("Operator [] - poza zasięgiem na plus"){

  double Tx[SIZE] = {-2,0,1};
  Vector3D x(Tx);

  WARN_THROWS(x[SIZE]);
}

TEST_CASE("Operator [] - poza zasięgiem na minus"){

  double Tx[SIZE] = {-2,0,1};
  Vector3D x(Tx);

  WARN_THROWS(x[-1]);
}

TEST_CASE("Porownanie - minimalnie nierowne"){
  
  double Tx[SIZE] = {1,1,1};
  double Ty[SIZE] = {1,1,1.01};

  Vector3D x(Tx), y(Ty);

  CHECK(!(x == y));
}

TEST_CASE("Porownanie - minimalnie rowne"){
  
  double Tx[SIZE] = {1,1,1};
  double Ty[SIZE] = {1,1,1.009};

  Vector3D x(Tx), y(Ty);

  CHECK(x == y);
}

TEST_CASE("Odległość między punktami"){

  double Tx[SIZE] = {1,1,1};
  double Ty[SIZE] = {-2,5,13};

  Vector3D x(Tx), y(Ty);

  CHECK(Distance(x, y) == 13);
}

TEST_CASE("Odległość między punktami - zero"){

  double Tx[SIZE] = {1,1,1};

  Vector3D x(Tx), y(Tx);

  CHECK(Distance(x,y) == 0);
}

TEST_CASE("Wyświetlanie"){

  double Tx[SIZE] = {5,2, 3};
  Vector3D x(Tx);

  std::stringstream out;

  out << x;

  CHECK("5.00000 2.00000 3.00000 \n" == out.str());
}

TEST_CASE("Wczytywanie"){

  std::stringstream in("2 \n 3 \n 5");
  double Ty[SIZE] = {2,3,5};
  Vector3D x, y(Ty);

  in >> x;

  CHECK(x == y);
}

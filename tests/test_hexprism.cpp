/*!
* \file
* \brief Plik zawiera testy dotyczące klasy HexPrism
*/

#include "../tests/doctest/doctest.h"
#include "../inc/hexprism.hh"

TEST_CASE("Tranformowanie układu współrzędnych - kąt 0"){

  HexPrism x;
  double Tp[SIZE] = {2,3,0};
  double Tv[SIZE] = {1,2,-1};
  double Tr[SIZE] = {3,5,-1};
  Vector3D p(Tp), v(Tv), r(Tr);
  x.SetPosition(p, 0);
  
  v = x.TransformToParentsCoords(v);

  CHECK(v == r);
}

TEST_CASE("Tranformowanie układu współrzędnych - kąt 90"){

  HexPrism x;
  double Tp[SIZE] = {2,3,0};
  double Tv[SIZE] = {1,2,-1};
  double Tr[SIZE] = {0, 4, -1};
  Vector3D p(Tp), v(Tv), r(Tr);
  x.SetPosition(p, 90);
  
  v = x.TransformToParentsCoords(v);

  CHECK(v == r);
}

TEST_CASE("Obracanie"){

  HexPrism x;
  double Tp[SIZE] = {2,3,0};
  double Tv[SIZE] = {1,2,-1};
  double Tr[SIZE] = {0, 4, -1};
  Vector3D p(Tp), v(Tv), r(Tr);
  x.SetPosition(p, 0);
  x.Rotate(90);
  
  v = x.TransformToParentsCoords(v);

  CHECK(v == r);

}
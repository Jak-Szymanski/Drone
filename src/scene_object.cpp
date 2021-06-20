/*!
* \file 
* \brief Definicje metod klasy SceneObject
*/

#include "../inc/scene_object.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"
#include "../inc/drone.hh"
#include <fstream> 

/*! 
* Obliczanie i wpisanie do odpowiedniego pliku globalnych współrzędnych obiektu sceny, na podstawie jego lokalnych współrzędnych i innych parametrów
*/
void SceneObject::CalcGlobalCoords(){

  std::ifstream local(TakeFileName_LocalCoords());
  std::ofstream global(TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");

  while(true){
    for(int i = 0; i < 4; ++i){
      local >> point;
      if( local.eof()) return;
      point = TransformToParentsCoords(point);

      global << point;
    }
    global << std::endl;
  }
}

/*!
* Detekcja kolizji pomiędzy obiektem sceny i dronem (w plaszczyźnie XY)
* Obiekt sceny jest przyblizony jako prostokąt równoległy do osi OX i OY
* Dron jest przybliżony jako okrąg
* \param[in] drone - Dron jako obiekt sceny
*
* \return 1 jeżeli zachodzi kolizja, 0 jeżeli nie
*/
bool SceneObject::DetectCollision(SceneObject *drone){

  Drone* drone_cast = static_cast<Drone*>(drone);

  double distance_x = abs(drone_cast->ReturnPosition()[0] - ReturnPosition()[0]);   //wspolrzednie x i y odleglosci miedzy obiektami
  double distance_y = abs(drone_cast->ReturnPosition()[1] - ReturnPosition()[1]);
  double width = ReturnScale()[0];    //wymiary przeszkody
  double height = ReturnScale()[1];
  double drone_radius = 12;

  if (distance_x > (width/2 + drone_radius)) return false;    //okrag na pewno poza prostokątem
  if (distance_y > (height/2 + drone_radius)) return false;

  if(distance_x <= width/2) return true;    //okrag na pewno wewnatrz prostokata 
  if(distance_y <= height/2) return true;

  double corner_distance = sqrt(pow(distance_x - width/2, 2) + pow(distance_y - height/2, 2));  //odleglosc pomiedzy srodkiem okregu a najblizszym wierzcholkiem prostokata

  return (corner_distance <= drone_radius);
}



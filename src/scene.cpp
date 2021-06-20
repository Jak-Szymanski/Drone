/*!
* \file 
* \brief Definicje metod klasy Scene
*/

#include <bits/stdc++.h>
#include <memory>
#include <iostream>
#include "../inc/scene.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"

/*!
* \brief Domyślna nazwa pliku ze wspolrzednymi globalnymi przeszkody
*/
#define PLIK_WLASCIWY_PRZESZKODA         "../datasets/PlikWlasciwy_Przeszkoda"

/*!
* \brief Domyślna nazwa pliku ze wspolrzednymi lokalnymi przeszkody
*/
#define PLIK_ROBOCZY_PRZESZKODA          "../datasets/PlikRoboczy_Przeszkoda"

/*!
* \brief Format pliku ze wspolrzednymi
*/
#define FORMAT_PLIKU                ".dat"



/*!
* Dodaj danego drona do sceny (dodaje do listy dronów oraz elementów powierzchni)
* \param[in] new_drone - dron, który będzie dodany do sceny
*/
void Scene::AddDrone(Drone *new_drone) {
  
  DroneArray.push_back(new_drone); 
  ObjectList.push_back(std::shared_ptr<Drone>(new_drone));
}

/*!
* Dodaj przeszkodę do sceny na podstawie parametrów geometrycznych i numeru typu
* \param[in] scale - Wektor skalowania wielkości przeszkody w trzech wymiarach
* \param[in] pos_x - Wspolrzedna x polozenia przeszkody
* \param[in] pos_y - Wspolrzedna y polozenia przeszkody
* \param[in] type - typ przeszkody (1 - gora ze szczytem, 2 - gora z grania, 3 - plaskowyz)
* \param[in] Lacze - łącze do rysowania za pomocą GNUPlota
*/
void Scene::AddObject(Vector3D scale, double pos_x, double pos_y, int type, PzG::LaczeDoGNUPlota &Lacze){

                                                                /*  v-- numer przeszkody dopisany do nazwy pliku--v  */
  std::string localfile = std::string(PLIK_ROBOCZY_PRZESZKODA) + std::to_string(ObjectList.size() - DroneArray.size()) + FORMAT_PLIKU;
  std::string globalfile = std::string(PLIK_WLASCIWY_PRZESZKODA) + std::to_string(ObjectList.size() - DroneArray.size()) + FORMAT_PLIKU; 
  std::shared_ptr<SceneObject> tmp;
  switch(type){

    case 1:{
      tmp = std::make_shared<Peak>(Peak(scale, pos_x, pos_y, localfile, globalfile));   // gora ze szczytem
    }
    break;

    case 2:{
      tmp = std::make_shared<Slope>(Slope(scale, pos_x, pos_y, localfile, globalfile)); // gora z grania
    }
    break;

    case 3:{
      tmp = std::make_shared<Flat>(Flat(scale, pos_x, pos_y, localfile, globalfile));   // plaskowyz
    }
    break;

    default:
      throw std::runtime_error("Niepoprawny typ przeszkody!");
    break;
  }
  ObjectList.push_back(tmp);
  Lacze.DodajNazwePliku(globalfile.c_str());
}

/*!
* Przenieś przeszkode o danym indeksie na nowe polozenie
* \param[in] pos_x - wspolrzedna x nowego polozenia przeszkody
* \param[in] pos_y - wspolrzedna y nowego polozenia przeszkody
* \param[in] index - nr przeszkody (1 = pierwsza przeszkoda w kolejności listy itd.)
*/
void Scene::MoveObject(double pos_x, double pos_y, int index){

  std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin();
  std::advance(it, index + DroneArray.size() - 1); 

  double T[SIZE] = {pos_x, pos_y, 0};
  Vector3D Pos(T);
  it->get()->SetPosition(Pos, it->get()->ReturnOrientation());
  it->get()->CalcGlobalCoords(); 
}

/*!
* Usun przeszkode ze sceny na podstawie numeru indeksu w liscie obiektów
* \param[in] index - nr przeszkody (1 = pierwsza przeszkoda w kolejności listy itd.)
* \param[in] Lacze - lacze do rysowania w GNUPlocie
*/
void Scene::DeleteObject(int index, PzG::LaczeDoGNUPlota &Lacze){

  std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin();
  std::advance(it, index + DroneArray.size() - 1);

  std::string local = it->get()->TakeFileName_LocalCoords();
  std::string global = it->get()->TakeFileName_GlobalCoords();
  Lacze.UsunNazwePliku(local);
  Lacze.UsunNazwePliku(global);
  remove(local.c_str());
  remove(global.c_str());
  ObjectList.erase(it);
}

/*!
* Wyswietl liste przeszkod na powierzchni razem z ich numerami i pozycjami
* \return 0 jeżeli nie ma żadnych przeszkód, 1 jeżeli są
*/
bool Scene::PrintObjects(){

  if(ObjectList.size() == DroneArray.size()) return 0;

  int j = 1;
  for(std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin(); it != ObjectList.end(); ++it){
    if(it->get()->ReturnType() != "Dron"){
      std::cout << j << ". Polozenie: " << it->get()->ReturnPosition() << "\tTyp:" << it->get()->ReturnType() << std::endl;
      ++j;
    }
  }
  return 1;
}

/*!
* Dekonstruktor sceny, usuwa wszystkie pliki ze wspolrzednymi przeszkod po zakonczeniu pracy programu
* Istnieje po to, żeby nie przechowywać niepotrzebnych plików ze wspolrzednymi, pozostałościach po kazdym poprzednim uzywaniu programu
*/
Scene::~Scene(){

  for(std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin(); it != ObjectList.end(); ++it){
    if(it->get()->ReturnType() != "Dron"){
      remove(it->get()->TakeFileName_GlobalCoords().c_str());
      remove(it->get()->TakeFileName_LocalCoords().c_str());
    }
  }
}

/*!
* Sprawdzanie czy aktywny dron koliduje z jakąkolwiek przeszkodą lub dronem
* \return Jeżeli dron koliduje, to nazwę typu obiektu sceny z którym koliduje, jeżeli nie - pusty string
*/
std::string Scene::CheckCollision(){

  for(std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin(); it != ObjectList.end(); ++it){
      if(it->get()->DetectCollision(DroneArray[ActiveDrone]) ){
        return it->get()->ReturnType(); 
      }
  }
  return "";
}
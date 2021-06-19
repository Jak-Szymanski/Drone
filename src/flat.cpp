
/*!
* \file 
* \brief Definicje metod klasy Flat
*/

#include "../inc/flat.hh"
#include <fstream> 

/*!
* Tworzy nowy plaskowyz (wygeneruj pliki ze wspolrzednymi) dla danych parametrów:
* \param[in] scale - Wektor skalowania plaskowyzu względem figury wzorcowej
* \param[in] pos_x - Współrzedna x polozenia plaskowyzu
* \param[in] pos_y - Wspolrzedna y polozenia plaskowyzu
* \param[in] localfile - Nazwa pliku zawierajacego wspolrzedne lokalne plaskowyzu
* \param[in] globalfile - Nazwa pliku zawierającego wspolrzedne globalne plaskowyzu
*/
Flat::Flat(Vector3D scale, double pos_x, double pos_y, std::string localfile, std::string globalfile){
  
  double TPos[SIZE] = {pos_x, pos_y, 0};
  Vector3D Pos(TPos);

  SetPosition(Pos, 0);
  SetFileNames(localfile, globalfile);
  Initiate(scale[0], scale[1], scale [2]);
  CalcGlobalCoords();
}

/*!
* Zamien wzorcowy prostopadloscian na plaskowyz wedlug pewnej skali
* \param[in] scale_x - Wspolrzedna x skali
* \param[in] scale_y - Wspolrzedna y skali
* \param[in] scale_z - Wspolrzedna z skali
*/
void Flat::Initiate( double scale_x, double scale_y, double scale_z){
  
  std::ifstream Template (Cuboid::TemplateFileName);
  std::ofstream Local (TakeFileName_LocalCoords());
  Vector3D point;
  double Tz[SIZE] = {0, 0, 0.5 * scale_z};
  Vector3D Translation_Z(Tz);

  if(!Template.is_open() || !Local.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
  SetScale(scale_x, scale_y, scale_z);

  for(int j = 0; j < 5; ++j){
    for(int i = 0; i < 4; ++i){
      Template >> point;
      if(Template.eof()) return;
      point = Scale(point);
      Local << point + Translation_Z;
      }
    Local << std::endl;
    }
}
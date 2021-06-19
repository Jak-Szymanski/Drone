
/*!
* \file
* \brief Definicje metod klasy Cuboid
*/

#include "../inc/cuboid.hh"
#include "../inc/matrix3x3.hh"
#include <fstream> 

/*!
* Nazwa pliku ze współrzędnymi wzorcowymi sześcianu
*/
std::string Cuboid::TemplateFileName;

/*!
* Przetłumaczanie danego punktu z układu lokalnego prostopadłościanu do układu współrzędnych o poziom wyższego (w przykładu układu drona)
* \param[in] Point - punkt w układzie lokalnym
*
* \return Punkt w układzie o poziom wyższym
*/
Vector3D Cuboid::TransformToParentsCoords(const Vector3D &Point) const{

  Vector3D result;
  Matrix3x3 MatRot;
  MatRot.RotationMatrix(Orientation);

  result = MatRot * Point;
  result = result + Position;

  return result;
}

/*!
* Tworzenie współrzędnych lokalnych prostopadłościanu na podstawie współrzędnych wzorcowych i skali
* \param[in] TemplateFile - nazwa w pliku w którym znajdują się współrżedne wzorcowe sześcianu
* \param[in] scale_x - wartość przez którą te współrzędne mają być przeskalowane w osi x
* \param[in] scale_y - wartość przez którą te współrzędne mają być przeskalowane w osi y
* \param[in] scale_z - wartość przez którą te współrzędne mają być przeskalowane w osi z
*
* \return 1 jeśli zostało to wykonane bez problemów, w przeciwnym razie 0
*/ 
void Cuboid::Initiate(double scale_x, double scale_y, double scale_z){
  
  std::ifstream Template (TemplateFileName);
  std::ofstream Local (TakeFileName_LocalCoords());
  Vector3D point;

  if(!Template.is_open() || !Local.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
  SetScale(scale_x, scale_y, scale_z);

  while(true){
  for(int i = 0; i < 4; ++i){
    Template >> point;
    if(Template.eof()) return;
    point = Scale(point);
    Local << point;
    }
  Local << std::endl;
  }
}
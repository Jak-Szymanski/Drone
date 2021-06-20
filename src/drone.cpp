
/*!
* \file 
* \brief Definicje metod klasy Drone
*/

#include "../inc/drone.hh"
#include "../inc/matrix3x3.hh"
#include <fstream>
#include <cmath>
#include <unistd.h>
/*!
* \brief Liczba pi
*/
#define PI 3.14159265358979323846

/*!
* \brief Odległość, którą dron przelatuje za każdym kolejnym rysowaniem lotu
*/
#define FLIGHT_INC 2

/*!
* \brief Kąt, o który obracają się rotory za każdym kolejnym rysowaniem lotu
*/
#define ROTOR_ROTATE_INC 10

/*!
* \brief Kąt, o który obraca się dron za każdym kolejnym rysowaniem lotu
*/
#define DRONE_ROTATE_INC 5

/*!
* \brief Skala korpusu względem wzorca (x, y, z)
*/
#define BODY_SCALE 10,8,4

/*!
* \brief Skala rotoru względem wzorca (x, y, z)
*/
#define ROTOR_SCALE 8,8,2

/*!
* \brief Pozycja korpusu względem drona (x, y, z)
*/
#define BODY_POS 0,0,2

/*!
* \brief Pozycja 1. rotoru względem drona (x, y, z)
*/
#define ROTOR0_POS 5,4,5

/*!
* \brief Pozycja 2. rotoru względem drona (x, y, z)
*/
#define ROTOR1_POS 5,-4,5

/*!
* \brief Pozycja 3. rotoru względem drona (x, y, z)
*/
#define ROTOR2_POS -5,4,5

/*!
* \brief Pozycja 4. rotoru względem drona (x, y, z)
*/
#define ROTOR3_POS -5,-4,5



/*! Obliczanie i wpisanie do odpowiedniego pliku globalnych współrzędnych danego rotora drona, na podstawie jego lokalnych współrzędnych i innych parametrów
* \param[in] Rotor - wskaźnik na dany rotor
*
* \return 1 jeśli zostało to wykonane bez problemów, w przeciwnym razie 0
*/
void Drone::CalcRotorGlobalCoords(const HexPrism &Rotor) const{

  std::ifstream local(Rotor.TakeFileName_LocalCoords());
  std::ofstream global(Rotor.TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
  while(local.is_open()){
    for(int i = 0; i < 4; ++i){
      if(!(local >> point)) return;
      point = Rotor.TransformToParentsCoords(point);
      point = TransformToParentsCoords(point);
      global << point;
    }
    global << std::endl;
  }
}

/*! Obliczanie i wpisanie do odpowiedniego pliku globalnych współrzędnych korpusu drona, na podstawie jego lokalnych współrzędnych i innych parametrów
*
* \return 1 jeśli zostało to wykonane bez problemów, w przeciwnym razie 0
*/
void Drone::CalcBodyGlobalCoords() const{

  std::ifstream local(Body.TakeFileName_LocalCoords());
  std::ofstream global(Body.TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");

  while(true){
    for(int i = 0; i < 4; ++i){
      local >> point;
      if( local.eof()) return;
      point = Body.TransformToParentsCoords(point);
      point = TransformToParentsCoords(point);

      global << point;
    }
    global << std::endl;
  }
}

/*!
* Przetłumaczanie danego punktu z układu lokalnego drona do układu współrzędnych o poziom wyższego (w przykładu układu globalnego)
* \param[in] Point - punkt w układzie lokalnym
*
* \return Punkt w układzie o poziom wyższym
*/
Vector3D Drone::TransformToParentsCoords(const Vector3D &Point) const{

  Vector3D result;
  Matrix3x3 MatRot;
  MatRot.RotationMatrix(Orientation);

  result = MatRot * Point;
  result = result + Position;

  return result;
}

/*!
* Oblicz punkty ścieżki dla danego lotu i wpisz do danego kontenera
* \param[in] angle - kąt w stopniach, na który dron powinien się obrócić podczas lotu
* \param[in] distance - pozioma odległość na którą dron powinien polecieć
* \param[in] PathPoints - wskaźnik na kontener zawierający punkty ścieżki przelotu
*/
void Drone::PlanPath (double angle, double distance, std::vector<Vector3D> &PathPoints){

  PathPoints.clear();
  double T_height[SIZE] = {0,0,80};
  double radians = (angle + Orientation)  * PI/180;
  double T_flight[SIZE] = {cos(radians)*distance, sin(radians)*distance, 0};
  Vector3D height(T_height);
  Vector3D flight(T_flight);

  PathPoints.push_back(Position);
  PathPoints.push_back(Position + height);
  PathPoints.push_back(Position + height + flight);
  PathPoints.push_back(Position + flight);
}

/*!
* Przedłuż ściężke o daną długość w kierunku w którym zmierza
* \param[in] distance - długość o którą przedłużamy istniejącą ścieżkę
* \param[in] PathPoints - wskaźnik na kontener zawierający punkty ścieżki przelotu
*/
void Drone::ExtendPath(double distance, std::vector<Vector3D> &PathPoints){

  double radians = (Orientation)  * PI/180;
  double T_flight[SIZE] = {cos(radians)*distance, sin(radians)*distance, 0};
  Vector3D flight(T_flight), tmp1, tmp2;

  tmp2 = PathPoints.back();   //skopiuj i usuń ostatni punkt
  PathPoints.pop_back();

  tmp1 = PathPoints.back();   //skopiuj i usuń przedostatni punkt
  PathPoints.pop_back();

  tmp1 = tmp1 + flight;       //przedłuż je o odpowiedni wektor
  tmp2 = tmp2 + flight;

  PathPoints.push_back(tmp1);
  PathPoints.push_back(tmp2);
}

/*!
* Obróć każdy z rotorów drona o dany kat, w odpowiednim kierunku odpowiadającym kierunkowi obrotu rotorów rzeczywistego drona
* \param[in] degrees - kąt obrotu rotorów w stopniach
*/
void Drone::SpinRotors(double degrees){
  
  Rotor[0].Rotate(degrees);
  Rotor[1].Rotate(-degrees);
  Rotor[2].Rotate(degrees);
  Rotor[3].Rotate(-degrees); 
}

/*!
* Wykonaj i wyrysuj lot pionowy drona na daną wysokość
* \param[in] distance - wysokość (może być również ujemna)
* \param[in] Lacze - łącze do rysowania za pomocą GNUPlota
*/
void Drone::VerticalFlight(double distance, PzG::LaczeDoGNUPlota &Lacze){

  CalcDroneGlobalCoords();
  double inc;
  distance > 0 ? inc=FLIGHT_INC : inc=-FLIGHT_INC;
  double T[3] = {0,0,inc};
  Vector3D trans(T);

  for(int i = 0; i < abs(distance); i+=FLIGHT_INC){
    SpinRotors(ROTOR_ROTATE_INC);
    Position = Position + trans;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

/*!
* Wykonaj i wyrysuj lot poziomy drona na daną odległość
* \param[in] distance - odległość
* \param[in] Lacze - łącze do rysowania za pomocą GNUPlota
*/
void Drone::HorizontalFlight(double distance, PzG::LaczeDoGNUPlota &Lacze){

  double radians = Orientation * PI/180;
  double x_inc = cos(radians) * FLIGHT_INC;
  double y_inc = sin(radians) * FLIGHT_INC;
  double T[3] = {x_inc, y_inc,0};
  Vector3D trans(T);
  CalcDroneGlobalCoords();

  for(int i = 0; i < distance; i+=FLIGHT_INC){
    SpinRotors(ROTOR_ROTATE_INC);
    Position = Position + trans;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

/*!
* Wykonaj i wyrysuj obrót drona względem własnej osi z o pewien kąt
* \param[in] degrees - kąt w stopniach
* \param[in] Lacze - łącze do rysowania za pomocą GNUPlota
*/
void Drone::Rotate(double degrees, PzG::LaczeDoGNUPlota &Lacze){

  CalcDroneGlobalCoords();

  for(int i = 0; i < degrees; i+=DRONE_ROTATE_INC){
    SpinRotors(ROTOR_ROTATE_INC);
    Orientation += DRONE_ROTATE_INC;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

/*! 
* Obliczanie i wpisanie do odpowiedniego pliku globalnych współrzędnych drona, na podstawie jego lokalnych współrzędnych i innych parametrów
*/
void Drone::CalcDroneGlobalCoords() const{

  CalcBodyGlobalCoords();
  for(int i = 0; i < 4; ++i){
    CalcRotorGlobalCoords(Rotor[i]);
  }
}

/*! 
* Ustawienie nazw plików zawierających współrzędne elementów drona
* \param[in] filenames - tablica z nazwami w danej kolejności: lokalne korpusu, globalne korpusu, lokalne Rotora1, globalne Rotora1 ... (następnie tak samo dla pozostałych rotorów)
*/
void Drone::SetCoordFiles(const std::string filenames[7]){

  Body.SetFileNames(filenames[0], filenames[1]);
  Rotor[0].SetFileNames(filenames[2], filenames[3]);
  Rotor[1].SetFileNames(filenames[2], filenames[4]);
  Rotor[2].SetFileNames(filenames[2], filenames[5]);
  Rotor[3].SetFileNames(filenames[2], filenames[6]);
}

/*!
* Tworzenie współrzędnych lokalnych prostopadłościanu na podstawie współrzędnych wzorcowych jego elementów i położenia
* \param[in] filenames - tablica zawierająca odpowiednio: nazwę pliku z współrzędnymi wzorcowymi sześcianu i graniastosłupa
* \param[in] scale_x - współrzędna x-owa położenia drona
* \param[in] scale_y - współrzędna y-owa położenia drona
* \param[in] scale_z - współrzędna z-owa położenia drona
*/
void Drone::Initiate(double pos_x, double pos_y, double pos_z, double angle){

  double TBody[SIZE] = {BODY_POS};
  double TR0[SIZE] = {ROTOR0_POS};
  double TR1[SIZE] = {ROTOR1_POS};
  double TR2[SIZE] = {ROTOR2_POS};
  double TR3[SIZE] = {ROTOR3_POS};

  double TDrone[SIZE] = {pos_x, pos_y, pos_z};

  Vector3D VBody(TBody), VR0(TR0), VR1(TR1), VR2(TR2), VR3(TR3), VDrone(TDrone);    // pozycje poszczególnych ciał względem drona

  Position = VDrone;
  Orientation = angle;

  Body.SetPosition(VBody, 0);
  Rotor[0].SetPosition(VR0, 0);
  Rotor[1].SetPosition(VR1, 0);
  Rotor[2].SetPosition(VR2, 0);
  Rotor[3].SetPosition(VR3, 0);

  Body.Initiate(BODY_SCALE);
  for(int i=0; i<4; i++){
    Rotor[i].Initiate(ROTOR_SCALE);
  }
}

/*!
* Poleć do góry na standardową wysokość
* Poleć do przodu na odległość równą promieniowi
* Obróć dronem o 90 w kierunku lotu po okręgu
* Wykonaj lot po okręgu o promieniu podanym w argumencie i środku w miejscu na który dron się początkowo wzniósł
* Obróć dronem o kolejne 90 i wróć na środek okręgu
* Wyląduj w miejscu z którego dron wystartował
* \param[in] radius - promień okręgu
* \param[in] Lacze - łącze do rysowania za pomocą GNUPlota
*/
void Drone::GoAround(double radius, PzG::LaczeDoGNUPlota &Lacze){

  double T[SIZE] = {cos(Orientation * PI/180) * radius, sin(Orientation * PI/180) * radius, 0};
  Vector3D RadiusVector(T);         // Obracający się wektor

  VerticalFlight(80, Lacze);
  Vector3D InitialPos(Position);    // Zapamiętaj położenie środka okręgu
  HorizontalFlight(radius, Lacze);

  Matrix3x3 MatRot;
  MatRot.RotationMatrix(DRONE_ROTATE_INC);

  Rotate(90, Lacze);
  for(int i = 0; i < 360; i+=DRONE_ROTATE_INC){
    RadiusVector = MatRot * RadiusVector;   // Pozycja podczas lotu po okręgu jest sumą wektora położenia środka okręgu
    Position = InitialPos + RadiusVector;   // i obracającego się wektora o długości równej promieniowi   
    Orientation += DRONE_ROTATE_INC;        
    SpinRotors(ROTOR_ROTATE_INC);
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj(); 
  }

  Rotate(90, Lacze);
  HorizontalFlight(radius, Lacze);
  VerticalFlight(-80, Lacze);
}

/*!
* Detekcja kolizji pomiędzy dwoma dronami
* Drony zostały w tym programie przybliżone jako okręgi o promieniu 10,5
* Poniższa metoda zakłada, że odległość pomiędzy dronami w płaszczyźnie XY powinna być większa od 23 (dodano trochę luzu)
* \param[in] drone - Dron jako obiekt sceny
*
* \return 1 jeżeli zachodzi kolizja, 0 jeżeli nie
*/
bool Drone::DetectCollision(SceneObject *drone){

  Drone* drone_cast = static_cast<Drone*>(drone);

  if(this == drone_cast){     // zeby dron nie sprawdzał kolizji sam ze sobą
    return false;
  }

  double distance = sqrt(pow(ReturnPosition()[0] - drone_cast->ReturnPosition()[0], 2) + pow(ReturnPosition()[1] - drone_cast->ReturnPosition()[1], 2));
  return distance <= 23;
}

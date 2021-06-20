#pragma once

/*!
* \file
* \brief Definicja klasy Drone
*
* Plik zawiera deklarację klasy określającą pojęcie dronu i jej metod
*/

#include "hexprism.hh"
#include "scene_object.hh"
#include "lacze_do_gnuplota.hh"

#include <iostream>
#include <vector>

/*!
* \brief Modeluje pojęcie dronu
*/
class Drone: public HexPrism, public SceneObject {

  private:

    /*!
    * \brief Pozycja dronu (względem globalnego układu współrzędnych)
    */
    Vector3D Position;

    /*!
    * \brief Kąt obrotu dronu (względem globalnego układu współrzędnych)
    */
    double Orientation;

    /*!
    * \brief Korpus drona
    */
    Cuboid Body;

    /*!
    * \brief Cztery rotory drona
    */
    HexPrism Rotor[4];

    /*!
    * \brief Oblicz współrzędne globalne korpusu drona
    */
    void CalcBodyGlobalCoords() const;

    /*!
    * \brief Oblicz współrzędne globalne rotoru drona
    */
    void CalcRotorGlobalCoords(const HexPrism &Rotor) const;

    /*!
    * \brief Obróć każdy z rotorów o pewien kąt w odpowiednim kierunku
    */
    void SpinRotors(double degrees);
    
  public:

    /*!
    * \brief Przetłumacz współrzędne lokalne drona na współrzędne globalne
    */
    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    /*!
    * \brief Zaplanuj ścieżkę przelotu drona
    */
    void PlanPath (double angle, double distance, std::vector<Vector3D> &PathPoints);

    /*!
    * \brief Przedłuż ścieżkę
    */
    void ExtendPath(double distance, std::vector<Vector3D> &PathPoints);

    /*!
    * \brief Wykonaj pioniowy lot drona na pewną odległość
    */
    void VerticalFlight (double distance, PzG::LaczeDoGNUPlota &Lacze);

    /*!
    * \brief Obróc drona o pewien kąt względem własnej osi z
    */
    void Rotate (double degrees, PzG::LaczeDoGNUPlota &Lacze);

    /*!
    * \brief Wykonaj poziomy lot drona na pewną odległość
    */
    void HorizontalFlight (double distance, PzG::LaczeDoGNUPlota &Lacze);

    /*!
    * \brief Wzleć do góry, poleć do przodu o pewną odległość, wykonaj lot po okręgu względem punktu do którego dron się początkowo wzniósł, wróć na poprzednie miejsce
    */
    void GoAround(double radius, PzG::LaczeDoGNUPlota &Lacze);

    /*!
    * \brief Oblicz współrzędne globalne drona
    */
    void CalcDroneGlobalCoords() const;

    /*!
    * \brief Ustal pliki zawierające współrzędne wszystkich elementów drona
    */
    void SetCoordFiles(const std::string filenames[7]);

    /*!
    * \brief Tworzenie drona według brył wzorcowych jego elementów, współrzędnych położenia i kątu obrotu
    */ 
    void Initiate(double pos_x, double pos_y, double pos_z, double angle);

    /*!
    * \brief Wyświetl pozycję drona w globalnym układzie współrzędnych
    */
    Vector3D ReturnPosition() override {return Position;};

    /*!
    * \brief Zwróć nazwę typu obiektu sceny
    */
    virtual std::string ReturnType() {return "Dron";};

    /*!
    * \brief Detekcja kolizji pomiędzy dwoma dronami
    */
    virtual bool DetectCollision(SceneObject *drone) override;
};
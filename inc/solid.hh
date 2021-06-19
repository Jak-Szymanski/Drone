#pragma once

/*!
* \file
* \brief Definicja klasy Solid
*
* Plik zawiera deklarację klasy określającą pojęcie bryły geometycznej i jej metod
*/

#include "vector3D.hh"
#include <stdio.h>
#include <string>

/*!
* \brief Modeluje pojęcie bryły geometycznej
*/
class Solid {

  private:

    /*!
    * \brief Nazwa pliku zawierającego lokalne współrzędne bryły
    */
    std::string FileName_LocalCoords;

    /*!
    * \brief Nazwa pliku zawierającego globalne współrzędne bryły
    */
    std::string FileName_GlobalCoords;

    /*!
    * \brief Wektor przez który bryła jest skalowana względem bryły wzorcowej
    */
    Vector3D Scale_Vector;

  public:

    /*!
    * \brief Ustawianie wektora skali
    *
    * Pozwala na podanie współrzędnych x, y i z wektora skali danej bryły podając je jako argumenty tej funkcji
    */
    void SetScale(double x, double y, double z) {Scale_Vector[0] = x; Scale_Vector[1] = y; Scale_Vector[2] = z;};

    /*!
    * \brief Skalowanie punktu przez wektor skali danej bryły
    * Zwraca współrzędne przeskalowanego punktu
    */
    Vector3D Scale (const Vector3D &Point) const{return Scale_Vector * Point;};

    /*!
    * \brief Zwracanie nazwy pliku zawierającego lokalne współrzędne bryły
    */
    const std::string &TakeFileName_LocalCoords() const {return FileName_LocalCoords;};

    /*!
    * \brief Zwracanie nazwy pliku zawierającego globalne współrzędne bryły
    */
    const std::string &TakeFileName_GlobalCoords() const {return FileName_GlobalCoords;};

    /*!
    * \brief Ustalanie nazw plików zawierających wspólrzędne danej bryły
    */
    void SetFileNames(std::string local, std::string global) {FileName_GlobalCoords = global; FileName_LocalCoords = local;};   

    Vector3D ReturnScale() {return Scale_Vector;};
};
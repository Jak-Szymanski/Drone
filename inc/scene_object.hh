#pragma once

/*!
* \file
* \brief Definicja klasy SceneObject
*
* Plik zawiera deklarację klasy określającą pojęcie obiektu sceny
* Obiektem sceny jest zarówno dron, jak i przeszkoda na powierzchni
*/

#include "cuboid.hh"


class SceneObject: public Cuboid {

  public:

    /*!
    * \brief Oblicz wspolrzedne globalne obiektu sceny
    */ 
    void CalcGlobalCoords();

    /*!
    * \brief Zwróc nazwę typu obiektu sceny
    */
    virtual std::string ReturnType() {return "Nieznany typ";};
  
    /*!
    * \brief Sprawdź, czy dron koliduje z danym obiektem sceny
    */
    virtual bool DetectCollision(SceneObject *drone);

};
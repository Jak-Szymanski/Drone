#pragma once

/*!
* \file
* \brief Deklaracja klasy Cuboid
*
* Plik zawiera deklarację klasy określającą pojęcie prostopadłościanu i jej metod
*/

#include "solid.hh"

/*!
* \brief Modeluje pojęcie prostopadłościanu (będącym w tym programie korpusem dronu)
*/
class Cuboid: public Solid {

  private:

    /*!
    * \brief Pozycja prostopadłościanu (względem układu wspólrzędnych drona)
    */
    Vector3D Position;

    /*!
    * \brief Kąt obrotu prostopadłościanu (względem układu wspólrzędnych drona)
    */
    double Orientation;



  public:

    /*!
    * \brief Nazwa pliku ze współrzędnymi wzorcowymi sześcianu
    */
    static std::string TemplateFileName;

    /*!
    * \brief Przetłumacz współrzędne lokalne prostopadłościanu na współrzędne w układzie drona
    */
    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    /*!
    * \brief Ustal pozycję i orientację prostopadłościanu (względem układu drona)
    */
    void SetPosition(const Vector3D Pos, double angle) {Position = Pos; Orientation = angle;};

    /*!
    * \brief Tworzenie prostopadłościanu według bryły wzorcowej i skali 
    */
    virtual void Initiate(double scale_x, double scale_y, double scale_z);

    /*!
    * \brief Zwroc pozycje prostopadloscianu
    */
    virtual Vector3D ReturnPosition() {return Position;};

    /*!
    * \brief Zwroc orientacje prostopadloscianu
    */
    double ReturnOrientation() {return Orientation;};
};

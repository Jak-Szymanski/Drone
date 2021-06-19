#pragma once

/*!
* \file
* \brief Deklaracja klasy HexPrism
*
* Plik zawiera deklarację klasy określającą pojęcie graniastosłupa foremnego sześciokątnego i jej metod
*/

#include "cuboid.hh"

/*!
* \brief Modeluje pojęcie graniastosłupa foremnego sześciokątnego (będącym w tym programie rotorami dronu)
*/
class HexPrism: public Solid {

  private:

    /*!
    * \brief Pozycja graniastosłupa (względem układu wspólrzędnych drona)
    */
    Vector3D Position;

    /*!
    * \brief Kąt obrotu graniastosłupa (względem układu wspólrzędnych drona)
    */
    double Orientation;

  public:

    /*!
    * \brief Nazwa pliku ze współrzędnymi wzorcowymi graniastosłupa sześciokątnego
    */
    static std::string TemplateFileName;

    /*!
    * \brief Przetłumacz współrzędne lokalne graniastosłupa na współrzędne w układzie drona
    */
    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    /*!
    * \brief Ustal pozycję i orientację graniastosłupa (względem układu drona)
    */
    void SetPosition(const Vector3D Pos, double angle) {Position = Pos; Orientation = angle;};

    /*!
    * \brief Obracanie graniastosłupa według własnej osi z
    */
    void Rotate(const double rotation) {Orientation += rotation;};

    /*!
    * \brief Tworzenie graniastosłupa według bryły wzorcowej i skali 
    */
    void Initiate(double scale_x, double scale_y, double scale_z);

};
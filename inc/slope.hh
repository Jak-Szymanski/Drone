#pragma once

/*!
* \file
* \brief Definicja klasy Slope
*
* Plik zawiera deklarację klasy określającą pojęcie gory z grania i jej metod
*/

#include "scene_object.hh"

/*!
* \brief Modeluje pojęcie gory z grania
*/
class Slope: public SceneObject{

  private:

    /*!
    * \brief Tworzenie gory z grania według bryły wzorcowej i skali 
    */
    virtual void Initiate(double scale_x, double scale_y, double scale_z) override;

  public:

    /*!
    * \brief Konstruktor tworzenia nowej gory z grania z danymi parametrami
    */
    Slope(Vector3D scale, double pos_x, double pos_y, std::string localfile, std::string globalfile);

    /*!
    * \brief Zwroc nazwe typu obiektu sceny
    */
    virtual std::string ReturnType() {return "Gora z grania";};
};
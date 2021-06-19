#pragma once

/*!
* \file
* \brief Definicja klasy Peak
*
* Plik zawiera deklarację klasy określającą pojęcie gory ze szczytem i jej metod
*/

#include "scene_object.hh"

/*!
* \brief Modeluje pojęcie gory ze szczytem
*/
class Peak: public SceneObject{

  private:

    /*!
    * \brief Tworzenie gory ze szczytem według bryły wzorcowej i skali 
    */
    virtual void Initiate(double scale_x, double scale_y, double scale_z) override;

  public:

    /*!
    * \brief Konstruktor tworzenia nowej gory ze szczytem z danymi parametrami
    */
    Peak(Vector3D scale, double pos_x, double pos_y, std::string localfile, std::string globalfile);

    /*!
    * \brief Zwroc nazwe typu obiektu sceny
    */
    virtual std::string ReturnType() {return "Gora z ostrym szczytem";};
};
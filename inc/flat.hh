#pragma once

/*!
* \file
* \brief Definicja klasy Flat
*
* Plik zawiera deklarację klasy określającą pojęcie plaskowyzu i jej metod
*/

#include "scene_object.hh"

/*!
* \brief Modeluje pojęcie plaskowyzu
*/
class Flat: public SceneObject{

  private:

    /*!
    * \brief Tworzenie plaskowyzu według bryły wzorcowej i skali 
    */
    void Initiate(double scale_x, double scale_y, double scale_z) override;
    
  public:

    /*!
    * \brief Konstruktor tworzenia nowego plaskowyzu z danymi parametrami
    */
    Flat(Vector3D scale, double pos_x, double pos_y, std::string localfile, std::string globalfile);


    /*!
    * \brief Zwroc nazwe typu obiektu sceny
    */
    std::string ReturnType() override {return "Plaskowyz";};


};
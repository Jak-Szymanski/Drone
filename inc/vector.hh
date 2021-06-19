#pragma once

/*! 
* \file
* \brief Definicja szablonu Vector
*
* Plik zawiera definicję szablonu Vector oraz jego metod 
*/

#include "size.hh"
#include <iostream>
#include <math.h>

/*!
* \brief Dokładność z którą są porównywane współrzędne wektora
*/
#define MIN_DIFF 0.01

/*!
* \brief Modeluje pojęcie wektora o dowolnym rozmiarze i typie danych, które on zawiera
*/
template <typename Type, int Size>
class Vector {

private:

    /*!
    * \brief Tablica wektora
    */
    Type size[Size];

    /*!
    * \brief Liczba aktywych wektorów
    */
    static int ActiveNumVectors;

    /*!
    * \brief Liczba wszystkich wektorów
    */
    static int AllNumVectors;

public:

    /*!
    * \brief Konstruktor bezparametryczny  wektora
    */
    Vector();

    /*!
    * \brief Konstruktor parametryczy wektora z tablicą jako parametr
    */
    Vector(Type [Size]);

    /*!
    * \brief Konstruktor kopiujący wektora
    */
    Vector(const Vector<Type, Size> &vec);

    /*!
    * \brief Dekonstruktor wektora
    */
    ~Vector();

    /*!
    * \brief Zwróć liczbę aktywnych wektorów
    */
    static int ReturnActiveNumVectors() {return ActiveNumVectors;};

    /*!
    * \brief Zwróc liczbę wszystkich wektorów
    */
    static int ReturnAllNumVectors() {return AllNumVectors;};

    /*!
    * \brief Wyzeruj liczbę wszystkich wektorów (używane jedynie do testów)
    */
    static void ClearAllNumVectors() {AllNumVectors = 0;}; 

    /*!
    * \brief Przeciążenie operatora dodawania dwóch wektorów
    */
    Vector<Type, Size> operator + (const Vector<Type, Size> &v);

    /*!
    * \brief Przeciążenie operatora odejmowania dwóch wektorów
    */
    Vector<Type, Size> operator - (const Vector<Type, Size> &v);

    /*!
    * \brief Przeciążenie operatora mnożenia wektora przez zmienną
    */
    Vector<Type, Size> operator * (const Type &tmp);

    /*!
    * \brief Przeciążenie operatora mnożenia wektora przez wektor
    */
    Vector<Type, Size> operator * (const Vector<Type, Size> &v) const;

    /*!
    * \brief Przeciążenie operatora dzielenia wektora przez zmienną
    */
    Vector<Type, Size> operator / (const Type &tmp);

    /*!
    * \brief Przeciążenie operatora przyrównania wektorów
    */
    Vector<Type, Size> operator = (const Vector<Type, Size> &v);

    /*!
    * \brief Przeciążenie operatora indeksowania wektora (zwraca zmienną const)
    */
    const Type &operator [] (unsigned int index) const;

    /*!
    * \brief Przeciążenie operatora indeksowania wektora (zwraca zmienną modyfikowalną)
    */
    Type &operator [] (unsigned int index);

    /*!
    * \brief Przeciążenie operatora porównania dwóch wektorów
    */
    bool operator == (const Vector<Type, Size> &v) const;

    /*!
    * \brief Wyznacza odległość między dwoma punktami zapisanymi jako wektory
    */
    double Distance (const Vector<Type, Size> &v1, const Vector<Type, Size> &v2);

};

template<typename Type, int Size>
int Vector<Type,Size>::ActiveNumVectors=0;

template<typename Type, int Size>
int Vector<Type,Size>::AllNumVectors=0;

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w lewo dla wektora
*/
std::ostream &operator << (std::ostream &out, Vector<double, SIZE> const &tmp);

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w prawo dla wektora
*/
std::istream &operator >> (std::istream &in, Vector<double, SIZE> &tmp);



/*!
* Inicjalizuje zmienną typu wektor o danym typie danych i rozmiarze. Wypełnia ten wektor zerami.
*/
template <typename Type, int Size>
Vector<Type, Size>::Vector() {
    for (int i = 0; i < Size; ++i) {
        size[i] = 0;
    }
}


/*!
* Inicjalizuje zmienną typu wektor o podanym typie współrzędnych i rozmiarze.
* Wypełnia ten wektor wartościami zapisanymi w tablicy tmp.
* \param[in] tmp - tablica zawierająca wartości, które powinny być wpisane do inicjowanego wektora
*/
template <typename Type, int Size>
Vector<Type, Size>::Vector(Type tmp[Size]) {
    for (int i = 0; i < Size; ++i) {
        size[i] = tmp[i];
    }
}


/*!
* Dodawanie dwóch wektorów takiego samego typu i rozmiaru
* \param[in] this - Pierwszy składnik dodawania
* \param[in] v - Drugi składnik dodawania
*
* \return Sumę argumentów jako wektor tego samego typu i rozmiaru
*/ 

template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator + (const Vector<Type, Size> &v) {
    Vector<Type, Size> result;
    for (int i = 0; i < Size; ++i) {
        result[i] = size[i] + v[i];
    }
    return result;
}


/*!
* Odejmowanie dwóch wektorów takiego samego typu i rozmiaru
* \param[in] this - Pierwszy składnik odejmowania
* \param[in] v - Drugi składnik odejmowania
*
* \return Różnicę argumentów jako wektor tego samego typu i rozmiaru
*/ 
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator - (const Vector<Type, Size> &v) {
    for (int i = 0; i < Size; ++i) {
        size[i] -= v[i];
    }
    return *this;
}


/*!
* Mnożenie wektora przez zmienną typu takiego samego co współrzędne wektora
* \param[in] this - Pierwszy składnik mnożenia (wektor)
* \param[in] tmp - Drugi składnik mnożenia (zmienna Type)
*
* \return Iloczyn argumentów jako wektor tego samego typu i rozmiaru
*/ 
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator * (const Type &c) {
    for (int i = 0; i < Size; ++i) {
        size[i] *= c;
    }
    return *this;
}


template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator * (const Vector<Type, Size> &v) const{

    Vector<Type, Size> result;
    for(int i = 0; i < Size; ++i){
        result[i] = size[i] * v[i];
    }
    return result;
}

/*!
* Dzielenie wektora przez zmienną typu takiego samego co współrzędne wektora
* \param[in] this - Pierwszy składnik dzielenia (wektor)
* \param[in] tmp - Drugi składnik dzielenia (zmienna Type)
*
* \return Iloraz argumentów jako wektor tego samego typu i rozmiaru
*/ 
template <typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator / (const Type &tmp) {
    for (int i = 0; i < Size; ++i) {
        size[i] /= tmp;
    }

    return *this;
}

template<typename Type, int Size>
Vector<Type, Size> Vector<Type, Size>::operator = (const Vector<Type, Size> &v){
    for(int i = 0; i < Size; ++i){
        size[i] = v[i];
    }
    return *this;
}


/*! 
* Indeksowanie wektora (const)
* \param[in] this - Wektor
* \param[in] index - Nr indeksu, którego wartość chcemy odczytać z wektora
* 
* \return Wartość wektora w danym indeksie wyrażona jako wartość stała Type
*/
template <typename Type, int Size>
const Type &Vector<Type, Size>::operator [] (unsigned int index) const {
    if (index >= Size) {
        throw std::runtime_error("Error: Wektor jest poza zasiegiem \n");
    }
    return size[index];
}


/*! 
* Indeksowanie wektora (modyfikowalny)
* \param[in] this - Wektor
* \param[in] index - Nr indeksu, którego wartość chcemy odczytać z wektora
* 
* \return Wartość wektora w danym indeksie wyrażona jako wartość modyfikowalna Type
*/
template <typename Type, int Size>
Type &Vector<Type, Size>::operator[](unsigned int index) {
    return const_cast<Type &>(const_cast<const Vector *>(this)->operator[](index));
}

/*!
* Porównywanie wektorów tego samego typu i rozmiaru
* \param[in] this - Pierwszy wektor
* \param[in] v - Drugi wektor
*
* \return 1 jeżeli wektory mają takie same wartości, 0 jeżeli nie (przy pewnej określonej tolerancji)
*/
template <typename Type, int Size>
bool Vector<Type, Size>::operator == (const Vector<Type, Size> &v) const {
    for (int i = 0; i < Size; ++i){
        if(abs(size[i] - v[i]) > MIN_DIFF){
            return 0;
        }
    }
    return 1;     
}


/*!
* Obliczanie odległości pomiędzy dwoma wektorami tego samego typu i rozmiaru
* \param[in] v1 - Pierwszy wektor
* \param[in] v2 - Drugi wektor
*
*\return Odległość pomiędzy dwoma punktami, których współrzędne są opisane wektorami podanymi w argumentach, jako zmienna typu double.
*/
template <typename Type, int Size>
double Distance (const Vector<Type, Size> &v1, const Vector<Type, Size> &v2){

    double result = 0;

    for (int i = 0; i < Size; ++i){
        result += pow((v1[i] - v2[i]),2);
    }
    result = sqrt(result);
    return result; 
}

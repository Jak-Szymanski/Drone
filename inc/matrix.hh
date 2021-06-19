#pragma once

/*! 
* \file
* \brief Definicja szablonu Matrix
*
* Plik zawiera definicję szablonu Matrix oraz jego metod 
*/

#include "vector.hh"
#include "vector3D.hh"
#include <iostream>
#include <cstdlib>

/*! 
* \brief Modeluje pojęcie macierzy kwadratowej o dowolnym rozmiarze i typie danych, które ona zawiera
*/
template <typename Type, int Size>
class Matrix {

private:
    /*!
    * \brief Wartości macierzy w tablicy dwuwymiarowej
    */
    Type value[Size][Size]; 

public:

    /*!
    * \brief Konstruktor bezparametryczny macierzy
    */
    Matrix(); 

    /*!
    * \brief Konstruktor parametryczny macierzy z tablicą jako parametr 
    */
    Matrix(Type [Size][Size]);                               

    /*! 
    * \brief Przeciążenie operatora mnożenia macierzy przez wektor
    */ 
    Vector<Type, Size> operator * (Vector<Type, Size> tmp);          

    /*!
    * \brief Przeciążenie operatora mnożenia macierzy przez macierz
    */
    Matrix<Type, Size> operator * (Matrix<Type, Size> tmp);        
    
    /*!
    * \brief Przeciążenie operatora dodawania dwóch macierzy
    */
    Matrix<Type, Size> operator + (Matrix<Type, Size> tmp);

    /*!
    * \brief Przeciążenie operatora wywołania (zwraca zmienną modyfikowalną)
    */
    Type  &operator () (unsigned int row, unsigned int column);

    /*!
    * \brief Przeciążenie operatora wywołania (zwraca zmienną const)
    */
    const Type &operator () (unsigned int row, unsigned int column) const;

    /*!
    * \brief Przeciążenie operatota porównania dwóch macierzy
    */
    bool operator == (const Matrix<Type, Size> &m) const;

    /*!
    * \brief Obliczanie trójwymiarowej macierzy obrotu 
    */
    void RotationMatrix (double degrees);

    /*!
    * \brief Uzyskanie macierzy jednostkowej
    */
    void IdentityMatrix();
};

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w prawo dla Macierzy3x3
*/
std::istream &operator>>(std::istream &in, Matrix<double, SIZE> &mat);

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w lewo dla Macierzy3x3
*/
std::ostream &operator<<(std::ostream &out, Matrix<double, SIZE> const &mat);

/*!
* \brief Przeciążenie operatora przesunięcia bitowego w lewo dla Macierzy4x4
*/
std::ostream &operator<<(std::ostream &out, Matrix<double, 4> const &mat);





/*!
* Inicjalizuje zmienną typu macierz o danym typie danych i rozmiarze. Wypełnia tą macierz zerami.
*/
template <typename Type, int Size>
Matrix<Type, Size>::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}


/*!
* Inicjalizuje zmienną typu macierz o podanym typie wartości i rozmiarze.
* Wypełnia tą macierz wartościami zapisanymi w tablicy tmp.
* \param[in] tmp - tablica zawierająca wartości, które powinny być wpisane do inicjowanej macierzy
*/
template <typename Type, int Size>
Matrix<Type, Size>::Matrix(Type tmp[Size][Size]) {
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}

/*!
* Mnożenie macierzy przez wektor o takim samym typie i odpowiadającym jej rozmiarze
* \param[in] this - Pierwszy składnik mnożenia (macierz)
* \param[in] tmp - Drugi składnik mnożenia (wektor)
*
* \return Iloczyn argumentów jako wektor tego samego typu i rozmiaru
*/
template <typename Type, int Size>
Vector<Type, Size> Matrix<Type, Size>::operator * (Vector<Type, Size> tmp) {
    Vector<Type, Size> result;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}

/*!
* Mnożenie dwóch macierzy tego samego typu i rozmiaru
* \param[in] this - Pierwszy składnik mnożenia 
* \param[in] tmp - Drugi składnik mnożenia 
*
* \return Iloczyn argumentów jako macierz tego samego typu i rozmiaru
*/
template <typename Type, int Size>
Matrix<Type, Size> Matrix<Type, Size>::operator * (Matrix<Type, Size> tmp) {

    Matrix<Type, Size> result;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            for (int k = 0; k < Size; ++k) {
                result.value[i][j] += value[i][k] * tmp(k, j);
            }
        }
    }
    return result;
}


/*!
* Dodawanie dwóch macierzy tego samego typu i rozmiaru
* \param[in] this - Pierwszy składnik dodawania
* \param[in] tmp - Drugi składnik dodawania
*
* \return Sumę argumentów jako macierz tego samego typu i rozmiaruwektory
*/
template <typename Type, int Size>
Matrix<Type, Size> Matrix<Type, Size>::operator + (Matrix<Type, Size> tmp) {
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            value[i][j] += tmp(i, j);
        }
    }
    return *this;
}

/*! 
* Uzyskiwanie wartości macierzy w danym punkcie jako zmienna const
* \param[in] this - Macierz
* \param[in] row - wiersz danego punktu
* \param[in] column - kolumna danego punktu
*
* \return Wartość macierzy w danym punkcie wyrażona jako wartość stała Type
*/
template <typename Type, int Size>
Type &Matrix<Type, Size>::operator()(unsigned int row, unsigned int column) {

    if (row >= Size) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= Size) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return value[row][column];
}

/*! 
* Pozyskiwanie wartości macierzy w danym punkcie jako zmienna modyfikowalna
* \param[in] this - Macierz
* \param[in] row - wiersz danego punktu
* \param[in] column - kolumna danego punktu
*
* \return Wartość macierzy w danym punkcie wyrażona jako wartość modyfikowalna Type
*/
template <typename Type, int Size>
const Type &Matrix<Type, Size>::operator () (unsigned int row, unsigned int column) const {

    if (row >= Size) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= Size) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return value[row][column];
}

/*!
* Porównywanie dwóch macierzy tego samego typu i rozmiaru
* \param[in] this - Pierwsza macierz
* \param[in] v - Druga macierz
*
* \return 1 jeżeli macierze mają takie same wartości, 0 jeżeli nie (przy pewnej określonej tolerancji)
*/
template <typename Type, int Size>
bool Matrix<Type, Size>::operator == (const Matrix<Type, Size> &m) const{
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            if(abs(value[i][j] - m(i, j)) >= MIN_DIFF){
                return 0;
            }
        }
    }
    return 1;
}

/*!
* Zmiana macierzy w macierz jednostkową
* \param[in] this - macierz
*/
template <typename Type, int Size>
void Matrix<Type, Size>::IdentityMatrix(){

    for (int i = 0; i < Size; ++i){
        for (int j = 0; j < Size; ++j){
            if(i == j){
                value[i][j] = 1;
            } else {
                value[i][j] = 0;
            }
        }
    }
}
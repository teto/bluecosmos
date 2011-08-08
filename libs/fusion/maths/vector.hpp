/**
* \file vector.h
* Class handling tables of 3 numbers ( integer or float ) which may be used either as vertex or vector
* \todo mettre certaisn "const" &
**/
#ifndef _FUSION_VECTOR_HPP_INCLUDED
#define _FUSION_VECTOR_HPP_INCLUDED

#include <fusion/core/ILogger.hpp>
#include <cmath>
#include <sstream>
#include <iostream>
#include <limits>// for std::numeric_limits
#include <SFML/System.hpp>

FUSION_NAMESPACE_BEGIN
template <typename T>
class CMatrix;

template<typename T,int N>
class CSquareMatrix;

template<typename T>
class CQuaternion;

template<class T>
class CVector {

public:
    CVector(const T& X,const T& Y,const T& Z = 0) : x(X),y(Y),z(Z){};
    CVector(const T*& table);

    CVector() : x(0),y(0),z(0){};

    //repasser en reference
      CQuaternion<T> operator*(const CQuaternion<T>& q) const;

    bool IsZero(float epsilon = 0) const;

    // Ce constructeur fait v2-v1 comme en maths:
    // le vecteur AB vaut B-A
    ////////////////////////////////////////////////////////////
    /// Constructor for OBB ( Oriented Bounding Boxes )
    ///
    /// \param v1
    /// \param v2
    ////////////////////////////////////////////////////////////
    CVector(const CVector<T>& v1,const CVector<T>& v2);

    ////////////////////////////////////////////////////////////
    /// Constructor for OBB ( Oriented Bounding Boxes )
    ///
    /// \param Lowest point
    ////////////////////////////////////////////////////////////
    void Set(const T& X,const T& Y,const T& Z = 0);


    void Set(const T* table);



    ////////////////////////////////////////////////////////////
    /// Constructor for OBB ( Oriented Bounding Boxes )
    ///
    /// \param Lowest point
    ////////////////////////////////////////////////////////////
    void Set(const CVector<T>& v1,const CVector<T>& v2);

    CVector<T> Normalized() const;
    void Normalize();
    T Length() const;
    T SquaredNorme() const;
    CQuaternion<T> ConvertToQuaternion();
    CMatrix<T> ConvertToMatrix() const;

    static T Cosinus(const CVector<T>& v,const CVector& u);
    static T Sinus(const CVector<T>& v,const CVector& u);
        //CVector<T> NormalVector(const CVector<T>& v);

//Redefinition de qques operateurs
    //Dot product
    CVector<T> operator^(CVector<T>& v) const;
    //Scalar product

    T operator*(const CVector<T>& v) const;


    CVector<T> operator*(const T& coeff) const;
    CVector<T> operator/(const T& divisor) const;

    CVector<T> operator-(const CVector<T>& v) const;//ok
    CVector<T> operator-() const;
    CVector<T> operator+(const CVector<T>& v) const;//ok
    CVector<T>& operator=(const CVector<T>& v);
    CVector<T>& operator += (const CVector<T>& v);
    CVector<T>& operator -= (const CVector<T>& v);
    CVector<T>& operator ^= (const CVector<T>& v);
    CVector<T>& operator *= (const CVector<T>& v);
    CVector<T>& operator *= (const T& coeff);
    CVector<T>& operator *= (const CSquareMatrix<T,3>& m);
    CVector<T>& operator *= (const CSquareMatrix<T,4>& m);
    //marche moyen pour des int
    CVector<T>& operator /= (const T& coeff);


    bool operator==(const CVector<T>& v) const;//ok
    bool operator!=(const CVector<T>& v1) const;//ok

    //For debug only
    std::string Display() const;

    std::ostream& operator <<(const CVector<T>& v);
    std::istream& operator >>(CVector<T>& v);

    ////////////////////////////////////////////////////////////
    /// Allow us to use both human-understandable method with x/y/z and
    /// GL functions applying to array ( for example glVertex3fuv )
    ////////////////////////////////////////////////////////////
    union {
        struct {
            T x,y,z;
        };
        T c[3];
    };
};

typedef CVector<int> TVectori;
typedef CVector<float> TVectorf;
typedef CVector<double> TVectord;


/*template<typename T>
T ScalarProduct(const CVector<T>& v1,const CVector<T>& v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z );
}*/

template<typename T>
void CreateOrthogonalBase(CVector<T>& v1,CVector<T>& v2,CVector<T>& v3);

template<typename T>
void CreateOrthonormalBase(CVector<T>& v1,CVector<T>& v2,CVector<T>& v3);

/**
\param direction
\param angle Angle in degree
**/
// TODO deplacer dans d'autres fichiers
template<typename T>
CVector<T> RandomVectorWithinACone(CVector<T> direction,const T& angle);

template<typename T>
CVector<T> RandomVectorWithinACone(CVector<T> direction,const T& angle,CVector<T> tangent,CVector<T> binormal);

#include "vector.inl"

FUSION_NAMESPACE_END


#endif

/**
* \file matrix.h
*/
#ifndef FUSION_MATRIX_SQUARE_H_INCLUDED
#define FUSION_MATRIX_SQUARE_H_INCLUDED


#include "matrix.hpp"
#include "vector.hpp"
#include "macros.hpp"
#include <cmath>
#include <limits>

FUSION_NAMESPACE_BEGIN

template<typename T,int N>
class CSquareMatrix : public CMatrix<T> {

public:

// a passer par reference constante dès que l'operateur () de CMatrix sera en int (...) const ;
    CSquareMatrix<T,N>& operator=(CSquareMatrix<T,N>& mat);

    CVector<T> GetTranslation() const ;
    void GetEulerAngles(float &x, float &y, float &z) const;


/*
        CVector<T>* ConvertToVector(){
            CVector<T> *v = NULL;
            if(mRows == 3 && mColumns == 1){
                v = new CVector<T>;
                v->x = (*this)(1,1);
                v->y = (*this)(2,1);
                v->z = (*this)(3,1);
            }
            return v;
        }*/

//CVector<T>& operator *(CVector<T>& v){
         CVector<T> Transform(const CVector<T>& v){

            CVector<T> res;

            if((N == 3) || ( N == 4 )){
/*
/:parce que la on utilise style opengl see mathlab.inl
  v = Vector3<Real>(
	  (v._x * _m11) + (v._y * _m21) + (v._z * _m31) + _tx,
	  (v._x * _m12) + (v._y * _m22) + (v._z * _m32) + _ty,
	  (v._x * _m13) + (v._y * _m23) + (v._z * _m33) + _tz
   );
   */
            res.Set( (*this)(1,1)*v.x + (*this)(1,2)*v.y + (*this)(1,3)*v.z,
                    (*this)(2,1)*v.x + (*this)(2,2)*v.y + (*this)(2,3)*v.z,
                    (*this)(3,1)*v.x + (*this)(3,2)*v.y + (*this)(3,3)*v.z ) ;
            /*
            res.Set( (*this)(1,1)*v.x + (*this)(2,1)*v.y + (*this)(3,1)*v.z,
                    (*this)(1,2)*v.x + (*this)(2,2)*v.y + (*this)(3,2)*v.z,
                    (*this)(1,3)*v.x + (*this)(2,3)*v.y + (*this)(3,3)*v.z ) ;
                    */
        }
        else {
            std::cout << "Error de multiplication de matrice par vecteur" << std::endl;
        }
        return res;
    }

    ////////////////////////////////////////////////////////////
    /// Constructor
    ////////////////////////////////////////////////////////////
    CSquareMatrix();

    ////////////////////////////////////////////////////////////
    /// Destructor
    ////////////////////////////////////////////////////////////
    //~CSquareMatrix();

    ////////////////////////////////////////////////////////////
    /// Compute the trace = sum of 1st diagonal coefficients
    ///
    /// \return float Value of the trace
    ///
    ////////////////////////////////////////////////////////////
    float Trace();

    ////////////////////////////////////////////////////////////
    /// Compte the inverse of the current matrix ( in case determinant is different
    /// from 0, otherwise throw an exception
    ///
    /// \return
    ///
    ////////////////////////////////////////////////////////////
    //CSquareMatrix<T,N> Inverse();


    ////////////////////////////////////////////////////////////
    /// Set current matrix as the Identity
    /// ( 0 everywhere except on the 1st diagonal => 1 )
    ////////////////////////////////////////////////////////////
    void Id();

    ////////////////////////////////////////////////////////////
    /// Compute the Determinant
    ///
    /// \return float The value of the determinant
    ////////////////////////////////////////////////////////////
    T Det();

    ////////////////////////////////////////////////////////////
    /// Tell if matrix symetric
    ///
    /// \return bool True if symetric,false otherwise
    ////////////////////////////////////////////////////////////
    bool Symetric();

protected:
    int mRank;
    int mRows,mColumns;//solution temporaire ?
};

#include "matrix_square.inl"

typedef class CSquareMatrix<float,4> TMatrix4f;
typedef class CSquareMatrix<float,3> TMatrix3f;


FUSION_NAMESPACE_END

#endif // FUSION_MATRIX_SQUARE_H_INCLUDED

/**
* \file matrix.h

definir scale/rotation etc...
implementer tous les operateurs
column-major
transferer certaines fonctions dans matrix.inl
*/

#ifndef FUSION_MATRIX_H_INCLUDED
#define FUSION_MATRIX_H_INCLUDED


#include "../core/exceptions.hpp"
#include <limits>
#include <cmath>

FUSION_NAMESPACE_BEGIN

template <typename T>
class CVector;


template <typename T>
class CMatrix {

public:
    ////////////////////////////////////////////////////////////
    /// Constructor
    ///
    /// \param Path to a file
    ///
    ////////////////////////////////////////////////////////////
    CMatrix(const int& rows,const int& columns);
    /*CMatrix(const CVector<T>& v) {
        mRows = 3;
        mColumns = 1;
        (*this)(1,1) = v.x;
        (*this)(2,1) = v.y;
        (*this)(3,1) = v.z;
    }
    */





    ////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /// \param Path to a file
    ///
    ////////////////////////////////////////////////////////////
    ~CMatrix();

//lancer des exceptions un peu partt
    T& operator()(const int& row,const int& column);
    //const float& operator()(const int& row,const int& column);
    //matrix constant ici en fait
    CMatrix<T>& operator +(CMatrix<T>& matrix);
    CMatrix<T>& operator +=(CMatrix<T>& matrix);
    CMatrix<T>& operator /(const T& divisor);

    CMatrix<T>& operator *(CMatrix<T>& matrix);

    //CMatrix& operator *(const T& matrix);
    //CMatrix& operator *=(const T& matrix);

    CMatrix<T>& operator =(CMatrix<T> matrix);
    bool operator ==(CMatrix<T>& matrix);
    bool operator !=(CMatrix<T>& matrix);


    CMatrix<T>& Transpose();



    static bool SameDimensions(const CMatrix<T>& m1,const CMatrix<T>& m2);

    void MultMatrix() { glMultMatrixf(mNumbers); };

//protected:
public:
//todo: verfiier que ce soit tjrs positif
    int mColumns,mRows;
    T *mNumbers;            //!< One dimension array 'cos faster to compute
};

//functions
#include "matrix.inl"

typedef CMatrix<float> TMatrixf;
typedef CMatrix<double> TMatrixd;

FUSION_NAMESPACE_END


#endif // FUSION_MATRIX_H_INCLUDED

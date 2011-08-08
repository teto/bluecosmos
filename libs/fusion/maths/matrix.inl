



//static
template <typename T>
bool CMatrix<T>::SameDimensions(const CMatrix<T>& m1,const CMatrix<T>& m2){
     if(  (m1.mColumns == m2.mColumns )  &&  ( m1.mRows == m2.mRows))
        return true;
    else
        return false;

}

template <typename T>
CMatrix<T>::CMatrix(const int& rows,const int& columns) : mColumns(columns),mRows(rows) {
    mNumbers = new T[rows * columns];
}

template <typename T>
CMatrix<T>::~CMatrix(){
    //delete[mRows * mColumns] mNumbers;
    delete[] mNumbers;
}


template <typename T>
CMatrix<T>& CMatrix<T>::operator /(const T& divisor){

	if(std::fabs(divisor) < std::numeric_limits<T>::epsilon()){
		//lancer une exception
	}
	CMatrix mat(mRows,mColumns);
    for(int l = 1 ; l <= mRows; l++){
        for(int c = 1; c <= mColumns; c++){
            mat(l,c) = (*this)(l,c) / divisor;

        }
    }
    return mat;
}


template <typename T>
CMatrix<T>& CMatrix<T>::operator +=(CMatrix<T>& matrix){

	//verifie les dimensions
	//if(matrix.mRows != mRows || matrix.mColumns != mColumns){
		//lancer une exception

	(*this) = (*this) + matrix;
    return (*this);
}

template <typename T>
CMatrix<T>& CMatrix<T>::operator +(CMatrix<T>& matrix){

	CMatrix mat(mRows,mColumns);


    if(!CMatrix<T>::SameDimensions( (*this),matrix ))
        return *this;

    for(int l = 1 ; l <= mRows; l++){
        for(int c = 1; c <= mColumns; c++){

            mat(l,c) =  matrix(l,c) +  (*this)(l,c);
        }
    }
    return mat;
}


template <typename T>
CMatrix<T>& CMatrix<T>::operator *(CMatrix<T>& matrix){


	//verifier les dimensions
    if(mColumns != matrix.mRows){
        /// \todo lancer une exception
    }

	CMatrix mat(mRows,mColumns);

    for(int l = 1 ; l <= mRows; l++){
        for(int c = 1; c <= matrix.mColumns; c++){
            for(int k = 1; k <= mRows; k ++ )
                mat(l,c) += (*this)(l,k)*matrix(k,c);

        }
    }
    return (*this);
}



//done
template <typename T>
bool CMatrix<T>::operator ==(CMatrix<T>& matrix){

    for(int l = 1 ; l <= mRows; l++){
        for(int c = 1; c <= mColumns; c++){
            if((*this)(l,c) != matrix(l,c)){
                return false;
            }
        }
    }
    return true;
}


template <typename T>
//CMatrix<T>& CMatrix<T>::operator=(CMatrix<T>& matrix){
CMatrix<T>& CMatrix<T>::operator=(CMatrix<T> matrix){

// \todo verifier les tailles deleter le tableau et le remettre a la meme taille
//    CMatrix mat(mRows,mColumns);

    for(int l = 1; l <= mRows; l++){
        for(int c = 1; c <= mColumns;c++){
            (*this)(l,c) = matrix(l,c);
        }
    }
    return (*this);
}




//done
template <typename T>
CMatrix<T>& CMatrix<T>::Transpose(){

	CMatrix mat(mColumns,mRows);

    for(int l = 1; l <= mRows; l++){
        for(int c = 1; c <= mColumns;c++){
            mat(l,c) = (*this)(c,l);
        }
    }

    return mat;//Row = mColumn;
}

/**
On stocke au format Opengl ligne par ligne ,de la gauche vers la droite et non de bas en haut
Example [ 0  4  8  12
          1  5  9  13
          2  6  10 14
          3  7  11 15 ]
**/
//est ce qu'on tient compte du decalage commencant à 0 ?
//faire en sorte que number
template <typename T>
T& CMatrix<T>::operator()(const int& row,const int& column){
    if(row > mRows || row < 1 || column > mColumns || column < 1){
        //exception
    }

    //sinon
    //le -1 est la car le premier element est stocke à l'indice 0 et non 1
    return mNumbers[(row-1)*mColumns + column -1 ];
}



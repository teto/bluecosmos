
template <typename T,int N>
CSquareMatrix<T,N>::CSquareMatrix() :
CMatrix<T>(N,N),mRank(N) {

//TEMPORAIRE ?
    mRows = mColumns = mRank;
}


template<typename T,int N>
CSquareMatrix<T,N>&
CSquareMatrix<T,N>::operator=(
CSquareMatrix<T,N>& mat
) {
  //CSquareMatrix<T,N>& operator=(CSquareMatrix<T,N>& mat);
    /*CMatrix<T> *temp = static_cast<CMatrix<T>*>(this);
    (*temp) = dynamic_cast<CMatrix<T> >(mat);*/
    //CMatrix<T>::operator=( static_cast<CMatrix<T> >(mat) );
    //return *this;

    for(int l = 1; l <= N; l++){
        for(int c = 1; c <= N;c++){
            (*this)(l,c) = mat(l,c);
        }
    }
    return (*this);
}


template <typename T,int N>
CVector<T>
CSquareMatrix <T,N>::GetTranslation() const {

	return CVector<T>( T(3,1), T(3,2), T(3,3) );
}	// end void GetTranslation(..)



// \todo faire des surcharges pour N = 2 ou N = 1 car fonctions valables juste pr N = 3 ou N = 4
template <typename T,int N>
void CSquareMatrix<T,N>::GetEulerAngles(float &x, float &y, float &z) const
{
	//%%%%%%%%%%%%%
	// NOT WORKING
	//%%%%%%%%%%%%%

	TVectord angle;		// temp angles
	double cy, tx, ty, sy;
/*
// a supprimer
	angle_y = -asin(m[2]);		// calculate y axis angle
	cy		= cos(angle_y);
*/

	//sy	= -m[2];
	sy	= -(*this)(3,1);
	cy	= std::sqrt(1 - SQRE(sy));
	angle.y	= std::atan2(sy, cy);

// no gimbal lock?
// 0.00003 = Epsilon ?
	if (0.0003 < std::fabs(cy)){
		tx	= T(3,3) / cy;		// get x axis angle
		ty	= T(3,2) / cy;

		angle.x	= atan2(ty, tx);

		tx	= T(1,1) / cy;		// get z axis angle
		ty	= T(2,1) / cy;

		angle.z	= std::atan2(ty, tx);
	}
	// gimbal lock
	else{
		angle.x	= 0.0f;			// set x axis angle to 0
		tx	= T(2,3);				// get z axis angle
		ty	= T(2,2);
		angle.z	= std::atan2(ty, tx);
	}

	x	= TO_DEG(angle.x);		// convert all to deg
	y	= TO_DEG(angle.y);
	z	= TO_DEG(angle.z);
/*
	LIMIT_RANGE(-180.0f, x, 180.0f);	// and limit them
	LIMIT_RANGE(-180.0f, y, 180.0f);
	LIMIT_RANGE(-180.0f, z, 180.0f);
*/
}
// end void GetEulerAngles(..)





// transfrom into identity
template <typename T,int N>
void CSquareMatrix<T,N>::Id(){

    for(int l = 1; l <= mRows; l++){
        for(int c = 1; c <= mColumns;c++){
            if( l == c )
                T(l,c) = 1;
            else
                T(1,c) = 0;
        }
    }
}


//ttes les matrices reelles diagonalisables

//expliquer la methode

template <typename T,int N>
T CSquareMatrix<T,N>::Det(){

/* on decide de faire confiance à l'utilisateur ???
    if(!mChanged)
        return mDeterminant
*/
    T mDeterminant = 0;

    if(mRows == 2){
        mDeterminant = (*this)(1,1)*(*this)(2,2) - (*this)(2,1)*(*this)(2,2);
    }
    else if(mRows == 3){
        mDeterminant = (*this)(1,1)*(*this)(2,2)*(*this)(3,3) + (*this)(2,1)*(*this)(3,2)*(*this)(1,3) + (*this)(3,1)*(*this)(1,2)*(*this)(2,3);
        mDeterminant -= (*this)(3,1)*(*this)(2,2)*(*this)(1,3) + (*this)(1,1)*(*this)(3,2)*(*this)(2,3) + (*this)(2,1)*(*this)(1,2)*(*this)(3,3);

    }
    int x,y; // <x> pour les colonnes <y> pour les lignes
    int i,j; // <i> pour les colonnes<j> pour les lignes
    int line_of_max,max,rank;

    // on copie <_mat> dans <mat> car on n'a pas le droit
    // de modifier les valeurs de la matrice <_mat>
    CSquareMatrix<T,N> mat();
    mat = (*this);

    // on calcule le determinant par la methode des pivots de Gauss
    // on rend la matrice triangulaire superieur tout en conservant
    // le mDeterminanterminant de la matrice a chaque iteration
    mDeterminant = 1;

    // on balaye les colonnes - 1 car a la derniere tt est deja range
    //en fait il s'agit des lignes ici ?
 for(int c = 1 ; c  <  mRows ; c++){

	 // ( etape 1 )
	 //on initialise le maximum a la valeur de [a]cc
	 line_of_max = c;
	 //On parcourt les lignes
	 for(int l = c + 1 ; l < mRows ; l++){
	 	if(std::fabs(mat(line_of_max,c)) < std::fabs(mat(l,c))){
			line_of_max = l;
		}
	 }

	 //valeur du coeff max
	 max = mat(line_of_max,c);

	 //si jamais le coeffmax vaut 0 alors matrice de la forme
 // ( a1 * * * * * ) [L1]
 // ( 0 a2 * * * * ) [L2]
 // ( 0 0 a3 * * * ) [L3]
 // ( 0 0 0 0 * * ) [L4]
// ( 0 0 0 0 * * ) [L5]
// ( 0 0 0 0 * * ) [L6]
	 // et signifie que le determinant est nul
	 /// \todo peut lancer une exception, la chopersi possible
	 if(std::fabs(max) <= std::numeric_limits<float>::epsilon()){
		mDeterminant = 0.;
		//goto label_end;
		 //verifier que ca marche
		 //on sort de la boucle for car c termine,le determinant vaut 0
		 break;
	 }

	 // si la ligne du maximum n'est pas de mm numero que celle de la colonne
	 if(line_of_max != c){

		 //on echange les lignes
		 float tmp = 0;
		 for( i = c ;  i < mRows ;  i++){

			 tmp = mat(c,i);
			 mat( c , i ) = mat( line_of_max , i );
			 mat( line_of_max, i ) = tmp;
		 }
		 // echanger 2 lignes multiplie le determinant par -1
		 mDeterminant *= -1.;
	 }

	// on multiplie le determinant par le coeff de la diagonale
	 mDeterminant *= max;



	 // maintenant on va mettre des 0 dans ttes les lignes en dessous de c
	 float coeff = 0; // c'est dans l'exemple le rapport 3/a4
	 for( rank= c+1; rank < mRows ; rank++){

		 coeff = mat( rank , c ) / max;

		 //a chaque colonne on retire coeff * [a]ci pour mettre des 0 en dessous de la ligne/colonne c/c
		 for( i = c ; i < mRows ; i++){
			mat( rank , i ) -= coeff*mat( c , i );
		 }
	 }

 }

 mDeterminant *= mat(mRows , mRows );
//label_end:
    return mDeterminant;
}



//http://www.developpez.net/forums/d35955/autres-langages/algorithmes/mathematiques/debutant-calculer-mDeterminanterminant-matrice/
//a deplacer dans CSquareMatrix
/// Concern only squared matrices
template <typename T,int N>
float CSquareMatrix<T,N>::Trace(){

    float trace = 0;
    for(int i; i < mRows;i++)
        trace += (*this)(i,i);
    return trace;
}



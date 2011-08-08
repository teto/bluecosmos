

template<class T>
CVector<T>::CVector(const T*& table) : x(0),y(0),z(0){
    Set(table);
};


template<class T>
void CVector<T>::Set(const T* table){

    try {
        x = table[0];
        y = table[1];
        z = table[2];
    }
    catch(...){
        ILogger::Log(EError) << "Too small an array for loading a vector";
    }
}

/*
inline CVector<T> NormalVector(const CVector<T>& v){
    //verifier cas ou x/y/z = 0
    //CVector<T> n(1,1,(-v.x-v.y)/v.z);

}*/
template<class T>
CVector<T>& CVector<T>::operator *= (const CSquareMatrix<T,3>& m){

    (*this) = m*(*this);
    return (*this);
}

template<class T>
CVector<T>& CVector<T>::operator *= (const CSquareMatrix<T,4>& m){
    (*this) = m*(*this);
    return (*this);
}

/*
template<class T>
CQuaternion<T> CVector<T>::operator*(const CQuaternion<T>& q) const {

// 1 ou 0 ?
    CVector<T> v = Normalized();
    //v.Set(x,y,z);
//std::cout << "v 1\t" << v.x << "/" << v.y << "/" << v.z << std::endl;
    //v.Normalize();
//std::cout << "this\t" << x << "/" << y << "/" << z << std::endl;
//std::cout << "v 2\t" << v.x << "/" << v.y << "/" << v.z << std::endl;

    CQuaternion<T> temp( v , 0 ); // ca c bon
    //std::cout << "temp avant\t" << temp.mVector.x << "/" << temp.mVector.y << "/" << temp.mVector.z << std::endl;
    temp = temp * q;

    //std::cout << "temp apres\t" << temp.mVector.x << "/" << temp.mVector.y << "/" << temp.mVector.z << std::endl;

    //std::cout << "operator* de CVector\t" << tmp.mVector.x << std::endl;
    return (temp) ;
}*/

template<class T>
CMatrix<T> CVector<T>::ConvertToMatrix() const {
    CMatrix<T> m(3,1);
            //mColumns = 1;
    m(1,1) = x;
    m(2,1) = y;
    m(3,1) = z;
    return m;
}


// remplacer par un std::abs(x) < epsilon
template<class T>
bool CVector<T>::IsZero(float epsilon) const {


    if( ( std::abs(x) <= epsilon ) && ( std::abs(y) <= epsilon) && ( std::abs(z) <= epsilon ) )
        return true;

    // otherwise
    return false;

}


template<class T>
inline T CVector<T>::Cosinus(const CVector<T>& v,const CVector<T>& u){

    return ( (v*u) / (v.Length()*u.Length()));
    //return ( v.Normalized()*u.Normalized());
}


template<class T>
inline T CVector<T>::Sinus(const CVector<T>& v,const CVector<T>& u){

    return ( v.Normalized() ^ u.Normalized()).Length();
}

template<class T>
CVector<T>& CVector<T>::operator=(const CVector<T>& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

template<class T>
inline CVector<T>::CVector(const CVector<T>& v1,const CVector<T>& v2){
    Set(v1,v2);
}

template<class T>
void CVector<T>::Set(const CVector<T>& v1,const CVector<T>& v2){
    x = v2.x - v1.x;
    y = v2.y - v1.y;
    z = v2.z - v1.z;
}

template<class T>
void CVector<T>::Set(const T& X,const T& Y,const T& Z){
    x = X;
    y = Y;
    z = Z;
}

//Dot product
template<class T>
CVector<T> CVector<T>::operator^(CVector<T>& v) const {

    CVector<T> temp;
    temp.x = (y * v.z) - (z * v.y);
    temp.y = (z * v.x) - (x * v.z);
    temp.z = (x * v.y) - (y * v.x);
    return temp;
}

//Scalar product
template<class T>
inline T CVector<T>::operator*(const CVector<T>& v) const {
    return (x*v.x + y*v.y + z*v.z );
}


template<class T>
inline T CVector<T>::SquaredNorme() const {
    return(x*x + y*y + z*z);
}


template<class T>
inline T CVector<T>::Length() const {
    return std::sqrt(SquaredNorme());
}



template<class T>
inline CVector<T> CVector<T>::Normalized() const {

    CVector<T> v = (*this);
    v /= Length();
    return v;
}


template<class T>
inline void CVector<T>::Normalize(){

    (*this) = Normalized();

}

template<class T>
std::string CVector<T>::Display() const {

    //std::string temp = "non implemented yet";
    std::ostringstream stream;
#if _FUSION_DEBUG
    stream << "Vector:\t"<< this->x <<"/"<<this->y<<"/"<<this->z<< std::endl;
    stream << "\tLength:\t"<<this->Length() << std::endl;
#endif
    return stream.str();
}



template<typename T>
inline bool CVector<T>::operator==(const CVector<T>& v) const {
    if(v.x == x && v.y == y && v.z == z)
        return true;
    return false;
}

template<typename T>
inline CVector<T> CVector<T>::operator+(const CVector<T>& v) const {
    return( CVector<T>(x+v.x,y+v.y,z+v.z) );
}

template<typename T>
CVector<T> CVector<T>::operator-() const {
    return( CVector<T>(-x,-y,-z) );
}

template<typename T>
inline CVector<T> CVector<T>::operator-(const CVector<T>& v) const {
    return( CVector<T>(x-v.x,y-v.y,z-v.z) );
}

template<typename T>
inline CVector<T> CVector<T>::operator*(const T& coeff) const {
    return( CVector<T>(x*coeff,y*coeff,z*coeff));
}

template<typename T>
inline CVector<T> CVector<T>::operator/(const T& divisor) const {
    if (std::abs(divisor) < std::numeric_limits<T>::epsilon()){
        //todo lancer une exception
        //throw
    }
    return( CVector<T>(x/divisor,y/divisor,z/divisor));
}

template<class T>
CVector<T>& CVector<T>::operator /= (const T& coeff){
    *this = *this/coeff;
    return *this;
}

template <class T>
inline CVector<T>& CVector<T>::operator +=(const CVector<T>& v) {
    Set(x + v.x , y + v.y , z + v.z);
    return (*this);
}


template <class T>
inline CVector<T>& CVector<T>::operator ^=(const CVector<T>& v) {
    (*this) = (*this)^v;
    return (*this);
}


template <class T>
inline CVector<T>& CVector<T>::operator -=(const CVector<T>& v) {
    (*this) += -v;
    return (*this);
}


template<typename T>
inline bool CVector<T>::operator!=(const CVector<T>& v1) const {
    if(v1 == this)
        return false;
    return true;
}


template <class T>
inline CVector<T>& CVector<T>::operator *=(const T& coeff) {
    (*this) = (*this)*coeff;
    return (*this);
}


//Operateurs de flux
// S'utilise comme suit:
template <class T>
inline std::istream& operator >>(std::istream& Stream,CVector<T>& v){
    Stream >> v.x >> v.y >> v.z;
    return Stream;
}

template <class T>
inline std::ostream& operator <<(std::ostream& Stream, const CVector<T>& v){
    return Stream << "x: " << v.x
                  << "\ty: " << v.y
                  << "\tz: " << v.z << std::endl;
}


    //creer une base orthonormee ( mettre dans une fonction a part )
    /////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void CreateOrthogonalBase(CVector<T>& v1,CVector<T>& v2,CVector<T>& v3){
// Builds a crude orthogonal-basis.
// Assumes, that Normal is a unit-vector (e.g. length(Normal) == 1)
//normal = directrice = mDirection;
  // Pick any Unit-Vector that's not orthogonal to Normal:
  //v1.Normalize();

// distinguer tous les cas pr etre sur que ca marche
  if (fabs(v1.x) > fabs(v1.y))
  {
    v2.x = 0;// utiliser set
    v2.y = 1;
    v2.z = 0;
  } else {
    v2.x = 1;
    v2.y = 0;
    v2.z = 0;
  }

  // build a binormal from tangent and normal:
  v3 = v2 ^ v1;

  // And correct the tangent from the binormal and the normal.
  v2 = v1 ^ v3;
  /*mDirection.Normalize();
  Normal.Normalize();
  Tangent.Normalize();*/
}

template<typename T>
void CreateOrthonormalBase(CVector<T>& v1,CVector<T>& v2,CVector<T>& v3){
    CreateOrthogonalBase(v1,v2,v3);
    v1.Normalize();
    v2.Normalize();
    v3.Normalize();
};

template<typename T>
CVector<T> RandomVectorWithinACone(CVector<T> direction,const T& angle){

    CVector<T> tangent,binormal;
    CreateOrthogonalBase(direction,tangent,binormal);

    return RandomVectorWithinACone(direction,angle,tangent,binormal);
}

template<typename T>
CVector<T> RandomVectorWithinACone(CVector<T> direction,const T& angle,CVector<T> tangent,CVector<T> binormal){

    T radius  = angle*direction.Length();
    T t = sf::Randomizer::Random(-radius,radius);
    T n = sf::Randomizer::Random(0.f,sqrt(radius*radius-t*t));

    CVector<T> temp = direction  + tangent * t  +  binormal * n;
    temp.Normalize();
    return temp;
}

// *****************************************************************************
template<class T>
inline cVector2<T>::cVector2()
: x(0)
, y(0)
{
}

// *****************************************************************************
template<class T>
inline cVector2<T>::cVector2(const T X, const T Y)
: x(X)
, y(Y)
{
}

// *****************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::Zero()
{
	return cVector2(0.0f, 0.0f);
}

// *****************************************************************************
template<class T>
inline bool cVector2<T>::IsZero() const
{
	return LengthSquared() < EpsilonFloat;
}

// *****************************************************************************
template<class T>
inline float cVector2<T>::Length() const
{
	return sqrt(LengthSquared());
}

// *****************************************************************************
template<class T>
inline float cVector2<T>::LengthSquared() const
{
	return (x * x + y * y);
}

// *****************************************************************************
template<class T>
inline void cVector2<T>::Normalize()
{
	float fLength = Length();

	if (fLength > EpsilonFloat)
	{
		x /= fLength;
		y /= fLength;
	}
}

// *****************************************************************************
template<class T>
inline float cVector2<T>::Dot(const cVector2 & inVec) const
{
	return x * inVec.x + y * inVec.y;
}

// *****************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::PerpendicularAboutXAxis() const
{
	return cVector2(y, -x);
}

// *****************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::PerpendicularAboutYAxis() const
{
	return cVector2(-y, x);
}

// *****************************************************************************
template<class T>
inline float cVector2<T>::Distance(const cVector2 & inVec) const
{
	return sqrt(DistanceSquared(inVec));
}

// *****************************************************************************
template<class T>
inline float cVector2<T>::DistanceSquared(const cVector2 & inVec) const
{
	float ySeparation = inVec.y - y;
	float xSeparation = inVec.x - x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}

// *****************************************************************************
template<class T>
inline void cVector2<T>::Reflect(const cVector2 & norm)
{
	*this += 2.0f * this->Dot(norm) * norm.GetReverse();
}

// *****************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::GetReverse() const
{
	return cVector2(-x, -y);
}

// ******************************************************************************
template<class T>
inline void cVector2<T>::AbsTo() 
{
	x = abs(x);
	y = abs(y);
}

// *******************************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::MajorAxis() const
{
	T absX = abs(x);
	T absY = abs(y);
	
	if(absX > absY)
	{
		T signX = static_cast<T>(Sign(x));
		return cVector2(signX, 0);
	}
	else
	{
		T signY = static_cast<T>(Sign(y));
		return cVector2(0, signY);
	}
}

// *******************************************************************************************
template<class T>
inline cVector2<T> cVector2<T>::MinorAxis() const
{
	T absX = abs(x);
	T absY = abs(y);
	
	if(absX < absY)
	{
		T signX = static_cast<T>(Sign(x));
		return cVector2(signX, 0);
	}
	else
	{
		T signY = static_cast<T>(Sign(y));
		return cVector2(0, signY);
	}
}

// *******************************************************************************************
template<class T>
inline void cVector2<T>::NegTo() 
{
	x = -x;
	y = -y;
}

// ******************************************************************************
template<class T>
inline const cVector2<T> & cVector2<T>::operator+=(const cVector2 & inVec)
{
	x += inVec.x;
	y += inVec.y;

	return *this;
}

// *****************************************************************************
template<class T>
inline const cVector2<T> & cVector2<T>::operator-=(const cVector2 & inVec)
{
	x -= inVec.x;
	y -= inVec.y;

	return *this;
}

// *****************************************************************************
template<class T>
inline const cVector2<T> & cVector2<T>::operator*=(const cVector2 & inVec)
{
	x *= inVec.x;
	y *= inVec.y;

	return *this;
}

// *****************************************************************************
template<class T>
inline const cVector2<T> & cVector2<T>::operator*=(const T Val)
{
	x *= Val;
	y *= Val;

	return *this;
}

// *****************************************************************************
template<class T>
inline const cVector2<T> & cVector2<T>::operator/=(const T Val)
{
	x /= Val;
	y /= Val;

	return *this;
}

// *****************************************************************************
template<class T>
inline bool cVector2<T>::operator==(const cVector2 & inVec) const
{
	return (isEqual(x, inVec.x) && isEqual(y,inVec.y));
}

// *****************************************************************************
template<class T>
inline bool cVector2<T>::operator!=(const cVector2 & inVec) const
{
	return (!isEqual(x, inVec.x) || !isEqual(y,inVec.y));
}

// *****************************************************************************
template<class T>
inline T & cVector2<T>::operator[](const unsigned int i)
{
	return *((&x) + i);
}

// *****************************************************************************
template<class T>
inline const T cVector2<T>::operator[](const unsigned int i) const
{
	return *((&x) + i);
}

// *****************************************************************************
template<class T>
cVector2<T> operator*(const cVector2<T> & inVec1, const T Val)
{
	cVector2 result(inVec1);
	result *= Val;
	return result;
}

// *****************************************************************************
template<class T>
cVector2<T> operator*(const T Val, const cVector2<T> & inVec1)
{
	cVector2 result(inVec1);
	result *= fVal;
	return result;
}

// *****************************************************************************
template<class T>
cVector2<T> operator/(const cVector2<T> & inVec1, const T Val )
{
	cVector2 result(inVec1);
	result /= Val;
	return result;
}

// *****************************************************************************
template<class T>
cVector2<T> operator-(const cVector2<T> & inVec1, const cVector2<T> & inVec2)
{
	cVector2 result(inVec1);
	result -= inVec2;
	return result;
}

// *****************************************************************************
template<class T>
cVector2<T> operator+(const cVector2<T> & inVec1, const cVector2<T> & inVec2)
{
	cVector2 result(inVec1);
	result += inVec2;
	return result;
}

// *****************************************************************************
template<class T>
cVector2<T> operator*(const cVector2<T> & inVec1, const cVector2<T> & inVec2)
{
	cVector2<T> result(inVec1);
	result *= inVec2;
	return result;
}

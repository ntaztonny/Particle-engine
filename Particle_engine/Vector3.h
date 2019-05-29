#ifndef Vector3_H
#define Vector3_H
#include <math.h>

class Vector3
{
public: float a,b,c;
public:
	Vector3(float x = 0, float y = 0, float z = 0)
	{
		a = x;
		b = y;
		c = z;
	}
	Vector3 operator+= (const Vector3 &vec)
	{
		return (*this= (*this+vec));
	
	}

	Vector3 operator+ (const Vector3 &vec)
	{
		return Vector3(a +vec.a, b+ vec.b, c + vec.c);
	
	}

	Vector3 operator-= (const Vector3 &vec)
	{
		return (*this= (*this-vec));
	
	}

	Vector3 operator- (const Vector3 &vec)
	{
		return Vector3(a -vec.a, b- vec.b, c - vec.c);
	
	}


	Vector3 operator* (const Vector3 &vec)
	{
		return Vector3(a *vec.a, b* vec.b, c * vec.c);
	
	}

	Vector3 operator/ (const Vector3 &vec)
	{
		return Vector3(a /vec.a, b/ vec.b, c / vec.c);
	
	}

	Vector3 operator* (float n)
	{
		return Vector3(a * n , b * n , c * n);
	
	}

	Vector3 operator/ (float n)
	{
		return Vector3(a / n , b / n , c / n);
	
	}

	Vector3 operator- (Vector3 &vec)
	{
		return Vector3(vec.a*-1, vec.b*-1, vec.c*-1 );
	
	}

	float dot(Vector3 m, Vector3 n)
	{
		return(m.a*n.a + m.b*n.b + m.c*n.c);
	}

	float length(void)
	{
		return (sqrt(a*a + b*b + c*c));
	}

	Vector3 normalize (void)
	{ 
		return (a/length(), b/length(), c/length());
	 
	}

};




#endif


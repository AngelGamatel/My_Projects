#pragma once
#include "libs.h"

class Vector0:public Vector
{
public:
	Vector0 ()=default;
	Vector0 (size_t);
	Vector0 (Fraction*, size_t);
	Vector0 (const Vector&);
public:
	int output(ostream&)const override;//не даст скомпилировать код в котором нет перегрузки
public: 
	Vector0 operator++(int);
	Vector0 operator--(int);
};

class Factory0:public Factory
{
public:
	Vector *CreateVector(istream&)const;
};

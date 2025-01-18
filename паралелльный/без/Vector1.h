#pragma once
#include "libs.h"

class Vector1:public Vector
{
public:
	Vector1 ()=default;
	Vector1(size_t);
	Vector1(Fraction*, size_t);
	Vector1 (const Vector&);
public:
	int output(ostream&)const override;//не даст скомпилировать код в котором нет перегрузки
public: 
	Vector1 operator++(int);
	Vector1 operator--(int);
};

class Factory1:public Factory
{
public:
	Vector *CreateVector(istream&)const;
};

#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <omp.h>
#include <chrono>
//#include <string> 


using namespace std;

class Fraction
{
private:
	int32_t num_;
	int32_t den_;
private:
	void Correct();
public:
	Fraction();
	Fraction(int32_t);
	Fraction(int32_t, int32_t);
public:
	void NumSet(int32_t);
	void DenSet(int32_t);
	int32_t NumGet()const;
	int32_t DenGet()const;
public:
	Fraction& operator+=(Fraction);
	Fraction& operator-=(Fraction);
	Fraction operator-()const;
	Fraction& operator*=(Fraction);
	Fraction& operator/=(Fraction);
		
};

Fraction operator+(Fraction, Fraction);
Fraction operator-(Fraction, Fraction);	
Fraction operator*(Fraction, Fraction);
Fraction operator/(Fraction, Fraction);	
istream& operator>>(istream&, Fraction&);

//~~~~~~~~~~~~~~~~~

class Vector0;

class Vector
{
protected:
/*	Fraction* data_;
	size_t size_;*/
	vector<Fraction> data_;
public:
	Vector()=default;
	Vector(size_t);
	Vector(Fraction*, size_t);
	Vector(const Vector& )=default;
	Vector(Vector&&)=default;
	//virtual ~Vector();
	
public:
	Vector& operator=(const Vector&)=default;
	Vector& operator=(Vector&&)=default;
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(const Fraction&);
	Vector& operator/=(const Fraction&);
	Vector& operator+=(const Fraction&);
	Vector& operator-=(const Fraction&);
	Vector& operator++();
	Vector& operator--();
	/*Vector operator++(int);
	Vector operator--(int); */
	Fraction& operator[](size_t);
	const Fraction& operator[](size_t)const;
public:
	size_t Size()const;
public:
	virtual int output(ostream&)const=0;
	virtual ~Vector()=default;
};

Vector0 operator+(const Vector&, const Vector&);
Vector0 operator-(const Vector&, const Vector&);	
Fraction operator*(const Vector&, const Vector&);
Vector0 operator++(Vector&, int);
Vector0 operator--(Vector&, int);
//Fraction operator/(const Vector&, const Vector&);	

//Vector *CreateData(const char *str)

class Factory
{
public:
	virtual Vector *CreateVector(istream&)const=0;
    virtual ~Factory()=default;
};

Vector *CreateData(std::istream& fin, Factory *f);



























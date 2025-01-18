#include "Vector0.h"

	Vector0::Vector0(size_t size):Vector(size){}
	
	Vector0::Vector0(Fraction* Fr, size_t size):Vector(Fr,size){}

	int Vector0::output(ostream& stream)const 
	{
		for(size_t i=0; i<data_.size(); i++)
		{
			stream << data_[i].NumGet() << "/" << data_[i].DenGet() << "; ";
		}
		stream << std::endl;
		return 1;	
	}

	Vector0 operator+(const Vector& f, const Vector& s)
	{
		return Vector0(f)+=s;
	}
	
	Vector0 operator-(const Vector& f, const Vector& s)
	{
		return Vector0(f)-=s;
	}
	
	Vector0::Vector0(const Vector& v):Vector(v){}
	
	Vector0 Vector0::operator++(int)
	{
		Vector0 new_vector(*this);
		++(*static_cast<Vector*>(this));
		return new_vector;
	}
	
	Vector0 Vector0::operator--(int)
	{
		Vector0 new_vector(*this);
		--(*static_cast<Vector*>(this));
		return new_vector;
	}
	
	Vector0 operator++(Vector& obj, int q)
	{
		Vector0 tmp = obj;
		++obj;
		return tmp;
	}
	
	Vector0 operator--(Vector& obj, int q)
	{
		Vector0 tmp = obj;
		--obj;
		return tmp;
	}	
	
	Vector* Factory0::CreateVector(istream& stream)const
	{
		size_t size;
		stream >> size;
		Vector* result=new Vector0(size);
		for(size_t i=0; i<size; i++)
		{
			stream >> (*result)[i];
		}
		return result; 
	}
	
	
	
	
	
	
	
	

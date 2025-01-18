#include "Vector1.h"

	Vector1::Vector1(size_t size):Vector(size){}
	
	Vector1::Vector1(Fraction* Fr, size_t size):Vector(Fr,size){}

	int Vector1::output(ostream& stream)const 
	{
		for(size_t i=0; i<data_.size(); i++)
		{
			stream << data_[i].NumGet() << "/" << data_[i].DenGet() << std::endl;
		}
		return 1;	
	}
	
	/*Vector1 operator+(const Vector& f, const Vector& s)
	{
		return Vector0(f)+=s;
	}
	
	Vector1 operator-(const Vector& f, const Vector& s)
	{
		return Vector0(f)-=s;
	}
	*/
	Vector1::Vector1(const Vector& v):Vector(v){}
	
	Vector1 Vector1::operator++(int)
	{
		Vector1 new_vector(*this);
		++(*static_cast<Vector*>(this));
		return new_vector;
	}
	
	Vector1 Vector1::operator--(int)
	{
		Vector1 new_vector(*this);
		--(*static_cast<Vector*>(this));
		return new_vector;
	}

	Vector* Factory1::CreateVector(istream& stream)const
	{
		size_t size;
		stream >> size;
		Vector* result=new Vector1(size);
		for(size_t i=0; i<size; i++)
		{
			stream >> (*result)[i];
		}
		return result; 
	}
	
	
	
	
	

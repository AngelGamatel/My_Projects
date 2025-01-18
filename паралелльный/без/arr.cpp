#include "libs.h"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

Fraction::Fraction():num_(0),den_(1){}

Fraction::Fraction(int32_t num):num_(num),den_(1){}

Fraction::Fraction(int32_t num,int32_t den):num_(num),den_(den)
{
	Correct();
}

void Fraction::Correct()
{
	//std::cout << "num  " <<num_ << endl;
	int32_t num=abs(num_);
	//std::cout << "num  " <<num << endl;
	int32_t den, ma, mi;
	//if(num!=num_) bool t=true;
	//num=abs(num);
	den=den_;
	ma=max(den,num);
	mi=min(den,num);
	while (mi)
	{
		int32_t buffer=mi;
		mi=ma%mi;
		ma=buffer;
	}
	//std::cout << "ma  " <<ma << endl;
	num_/=ma;
	den_/=ma;
	if(den_<0) 
	{
		den_*=-1;
		num_*=-1;
	}
}

void Fraction::NumSet(int32_t num)
{
	num_=num;
}
void Fraction::DenSet(int32_t den)
{
	den_=den;
}
int32_t Fraction::NumGet()const
{
	return num_;
}
int32_t Fraction::DenGet()const
{
	return den_;
}

Fraction& Fraction::operator+=(Fraction other)
{
	num_*=other.den_;
	other.num_*=den_;
	den_*=other.den_;
	//other.den=den_;
	num_+=other.num_;
	Correct();
	return *this;
}

Fraction Fraction::operator-()const
{
	Fraction Fr(*this);
	Fr.num_=-Fr.num_;
	return Fr;
}


Fraction& Fraction::operator-=(Fraction other)
{
	*this+= -other;
	return *this;
}

Fraction& Fraction::operator*=(Fraction other)
{
	num_*=other.num_;
	den_*=other.den_;
	Correct();
	return *this;
}

Fraction& Fraction::operator/=(Fraction other)
{
	num_*=other.den_;
	int32_t num;
	num=abs(other.num_);
	den_*=num;
	if(abs(other.num_)!=other.num_) *this= -(*this);
	Correct();
	return *this;
}
//gthtltkfnm
istream& operator>>(istream& stream, Fraction& fr)
{
	string str;
	stream >> str;
	int32_t numm=0;
	int32_t denn=0;
	size_t i=0;
	bool den_poss=true;
	bool num_poss=true;
	if(str[i]=='-')
	{
		num_poss = false;
		i++;
	}
	while(str[i]!='/' && str[i]!='\0')
	{
		numm=numm*10+str[i]-'0';
		i++;
	}
	if(!num_poss)
	{
		numm *= -1;
	}
	if(str[i]=='\0') 
	{
		fr=Fraction(numm);
	}
	else
	{
	i++;
	if(str[i]=='-')
	{
		den_poss = false;
		i++;
	}
	while(str[i]!='\0')
	{
		denn=denn*10+str[i]-'0';
		i++;
	}
	if(!den_poss)
	{
		denn *= -1;
	}
	
	fr=Fraction(numm, denn);
	}
	return stream;
}
//gthtltkfnm
Fraction operator+(Fraction f, Fraction s)
{
	return f+=s;
}
Fraction operator-(Fraction f, Fraction s)
{
	return f-=s;
}	
Fraction operator*(Fraction f, Fraction s)
{
	return f*=s;
}
Fraction operator/(Fraction f, Fraction s)
{
	return f/=s;
}	

//---------------------------------------------------------------------------------------

//Vector::Vector():data_(nullptr),size_(0){}

Vector::Vector(size_t size):data_(/*new Fraction[*/size/*]*/)/*,size_(size)*/{}

Vector::Vector(Fraction* Fr, size_t size):data_(/*new Fraction[*/size/*]*/)/*,size_(size)*/
	{
		for(size_t i=0; i<size; i++)
		{
			data_[i]=Fr[i];
		}
	}
	
/*Vector::Vector(const Vector& other):data_(new Fraction[other.size_]),size_(other.size_)
	{
		for(size_t i=0; i<size_; i++)
		{
			data_[i]=other.data_[i];
		}
	}
Vector::Vector(Vector&& other):data_(other.data_),size_(other.size_)
	{
		other.data_=nullptr;
	}

Vector& Vector::operator=(const Vector& other)
{
	if(this== &other) return *this;
	delete[] data_;
	size_=other.size_;
	data_=new Fraction[other.size_];
	for(size_t i=0; i< size_; i++)
	{
		data_[i]=other.data_[i];
	}
	return *this;
}

Vector& Vector::operator=(Vector&& other)
{
	if(this== &other) return *this;
	delete[] data_;
	data_=other.data_;
	size_=other.size_;
	other.data_=nullptr;
	return *this;
}*/

/*Vector::~Vector()
{
	size_=0;
	delete[] data_;
}*/

/*Factory::~Factory()
{
    
}*/

Vector& Vector::operator+=(const Vector& other)
{
	/*if (other.size_ > size_)
	{
		Fraction* new_data = new Fraction[other.size_];
		for(size_t i=0; i<size_; i++)
		{
			new_data[i]=data_[i];
		}
		delete[] data_;
		data_=new_data;
		size_=other.size_;
	}*/
	data_.resize(max(data_.size(),other.data_.size()),0);
	for(size_t i=0; i<other.data_.size(); i++)
	{
		data_[i]+=other.data_[i];
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
	/*if (other.size_ > size_)
	{
		Fraction* new_data = new Fraction[other.size_];
		for(size_t i=0; i<size_; i++)
		{
			new_data[i]=data_[i];
		}
		delete[] data_;
		data_=new_data;
		size_=other.size_;
	}*/
	data_.resize(max(data_.size(),other.data_.size()),0);
	for(size_t i=0; i<other.data_.size(); i++)
	{
		data_[i]-=other.data_[i];
	}
	return *this;
}

Vector& Vector::operator*=(const Fraction& other)
{
	for(size_t i=0; i<data_.size(); i++)
	{
		data_[i]*=other;
	}
	return *this;
}

Vector& Vector::operator/=(const Fraction& other)
{
	for(size_t i=0; i<data_.size(); i++)
	{
		data_[i]/=other;
	}
	return *this;
}

Vector& Vector::operator+=(const Fraction& other)
{
	for(size_t i=0; i<data_.size(); i++)
	{
		data_[i]+=other;
	}
	return *this;
}

Vector& Vector::operator-=(const Fraction& other)
{
	for(size_t i=0; i<data_.size(); i++)
	{
		data_[i]-=other;
	}
	return *this;
}

Vector& Vector::operator++()
{
	/*Fraction* new_data = new Fraction[size_+1];
	for(size_t i=0; i<size_; i++)
	{
		new_data[i]=data_[i];
	}
	new_data[size_]=data_[size_-1];
	delete[] data_;
	data_=new_data;
	size_++;
	return *this;*/
	data_.push_back(data_.back());
	return *this;
}

/*Vector Vector::operator++(int)
{
	Vector new_vector(*this);
	++(*this);
	return new_vector;
}
*/
Vector& Vector::operator--()
{
	/*Fraction* new_data = new Fraction[size_-1];
	for(size_t i=1; i<size_; i++)
	{
		new_data[i-1]=data_[i];
	}
	delete[] data_;
	data_=new_data;
	size_--;
	return *this;*/
	data_.pop_back();
	return *this;
}

/*Vector Vector::operator--(int)
{
	Vector new_vector(*this);
	--(*this);
	return new_vector;
}
*/
/*Vector operator+(const Vector& f, const Vector& s)
{
	return Vector(f)+=s;
}
Vector operator-(const Vector& f, const Vector& s)
{
	return Vector(f)-=s;
}*/	
Fraction operator*(const Vector& f, const Vector& s)
{
	Fraction result;
	size_t min_size=min(f.Size(), s.Size());
	for(size_t i=0; i< min_size; i++)
	{
		result+=f[i]*s[i];
	}
	return result;
}
/*Fraction operator/(const Vector& f, const Vector& s)
{
	Fraction result;
	size_t min_size=min(f.Size(), s.Size());
	for(int i=0; i< min_size; i++)
	{
		result+=f[i]/s[i];
	}
	return result;
}	
*/
Fraction& Vector::operator[](size_t position)
{
	return data_[position];
}

const Fraction& Vector::operator[](size_t position)const
{
	return data_[position];
}

size_t Vector::Size()const
{
	return data_.size();
}


Vector *CreateData(std::istream& fin, Factory *f)
{
	Vector *result=f -> CreateVector(fin); 
	return result;
}




















































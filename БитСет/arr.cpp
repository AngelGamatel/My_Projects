#include "libs.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~база
CSet::CSet():size_(0),set_(nullptr) {}//список инициализации

size_t CSet::Capacity(size_t size)
{
	size_t res= size/(sizeof(uint64_t)*8);
	if(size%(sizeof(uint64_t)*8) != 0)
	{
		res++;
	}
	//cout << res << endl;
	return res;
}

CSet::CSet(size_t n):size_(n),set_(new uint64_t[Capacity(size_)]) 
{
	for(size_t i=0; i<Capacity(size_); i++)
	{
		set_[i]=0;
	}
}

CSet::CSet(const CSet& other):size_(other.size_),set_(new uint64_t[Capacity(size_)])
{
	for(size_t i=0; i<Capacity(size_); i++)
	{
		set_[i]=other.set_[i];
	}
}

CSet::CSet(CSet&& other):size_(other.size_),set_(other.set_)
{
	other.set_=nullptr;
}

CSet::~CSet()
{
	delete[] set_;
}

CSet& CSet::operator=(const CSet& other)
{
	if(this==&other) return *this;
	uint64_t* new_set=new uint64_t[Capacity(other.size_)];
	for (size_t i=0; i<Capacity(other.size_); i++)
	{
		new_set[i]=other.set_[i];
	}
	delete[] set_;
	set_ = new_set;
	size_=other.size_;
	return *this;
}

CSet& CSet::operator=(CSet&& other)
{
	
	if(this==&other) return *this;
	delete[] set_;
	set_ = other.set_;
	size_=other.size_;
	other.set_=nullptr;
	return *this;
}

bool CSet::Bit(size_t index)const//достаём бит под номером index
{
	uint64_t current_sell=set_[index/(sizeof(uint64_t)*8)];
	size_t current_index=index%(sizeof(uint64_t)*8);
	return (current_sell>>current_index)%2==1;//true if 1, false if 0
	/*if ((current_sell>>current_index)%2==1) return true;
	if ((current_sell>>current_index)%2==0) return false;*/
}

bool CSet::operator[](size_t index) const
{
	return Bit(index);
}

CSet& CSet::operator|=(const CSet& other)//побитовое или
{
	if (Capacity(size_)<Capacity(other.size_))
	{
		uint64_t* new_set=new uint64_t[Capacity(other.size_)];
		for(size_t i=0; i<Capacity(size_);i++)
		{
			new_set[i]=set_[i];
		}
		for(size_t i=Capacity(size_); i<Capacity(other.size_); i++)
		{
			new_set[i]=0;
		}
		delete[]set_;
		set_=new_set;
	}
	for(size_t i=0; i<Capacity(other.size_);i++)
	{
		set_[i]|=other.set_[i];
	}
	size_=max(size_,other.size_);
	return *this; 
}

CSet& CSet::operator&=(const CSet& other)//побитовое И
{
	if (Capacity(size_)<Capacity(other.size_))
	{
		uint64_t* new_set=new uint64_t[Capacity(other.size_)];
		for(size_t i=0; i<Capacity(size_);i++)
		{
			new_set[i]=set_[i];
		}
		for(size_t i=Capacity(size_); i<Capacity(other.size_); i++)
		{
			new_set[i]=0;
		}
		delete[]set_;
		set_=new_set;
	}
	for(size_t i=0; i<Capacity(other.size_);i++)
	{
		set_[i]&=other.set_[i];
	}
	size_=min(size_,other.size_);
	return *this; 
}

CSet& CSet::operator++()
{
	size_++;
	return *this;
}

CSet CSet::operator++(int)
{
	CSet copy(*this);
	size_++;
	return copy;
}

CSet& CSet::operator--()
{
	size_--;
	return *this;
}

CSet CSet::operator--(int)
{
	CSet copy(*this);
	size_--;
	return copy;
}

void CSet::Print(ostream& stream) const
{
	for (size_t i=0; i<size_; i++)
	{
		if (Bit(i)) stream << 1; 
		else stream << 0; 
	}
	stream << endl;
}

void CSet::SetBit(size_t index, bool t)
{
	uint64_t& current_sell=set_[index/(sizeof(uint64_t)*8)];
	size_t current_index=index%(sizeof(uint64_t)*8);
	uint64_t one = 1;
	one<<=current_index;
	if(t)
	{ 
		current_sell|=one;
	} 
	else
	{
		one = ~one;
		current_sell&=one;
	}
}

CSet CSet::operator~()const
{
	CSet copy(*this);
	
	for(size_t i=0; i<Capacity(size_); i++)
	{
		copy.set_[i]=~set_[i];
	}
	return copy;
}

CSet operator+(const CSet& first, const CSet& second)
{
	return CSet(first)|=second;
}

CSet operator-(const CSet& first, const CSet& second)
{
	return CSet(first)&=~second;
}

CSet operator+(CSet&& first, const CSet& second)
{
	return first|=second;
}

CSet operator-(CSet&& first, const CSet& second)
{
	return first&=~second;
}





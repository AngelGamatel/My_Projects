#include <iostream>
#include <cstdint>
#include <memory>

using namespace std;

class CSet
{
private:
	size_t size_;
	unique_ptr<uint64_t[]> set_;//unsignet long long * с 64 битами
private:
	size_t Capacity(size_t size)const;//для вычисления колличества set
	bool Bit(size_t index)const;
public:
    CSet();
    CSet(size_t n);
    CSet(const CSet& other);
    CSet(CSet&& other);
    //~CSet();
public:
	CSet& operator=(const CSet& other);//по левой ссылке
	CSet& operator=(CSet&& other);//по правой ссылке
	bool operator[](size_t index)const;
	CSet& operator|=(const CSet& other);
	CSet& operator&=(const CSet& other);
	CSet& operator++();
	CSet& operator--();
	CSet operator++(int);
	CSet operator--(int);
	CSet operator~()const;
public:
	void Print(ostream& stream) const;
	void SetBit(size_t index, bool t);
};

CSet operator+(const CSet& first, const CSet& second);
CSet operator-(const CSet& first, const CSet& second);

CSet operator+(CSet&& first, const CSet& second);
CSet operator-(CSet&& first, const CSet& second);


















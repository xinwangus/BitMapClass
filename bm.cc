#include "bm.h"
#include <stdio.h>
#include <assert.h>


BitMap::BitMap():size(0)
{
}

BitMap::~BitMap()
{
}

BitMap* BitMap::bm = 0;
std::mutex BitMap::mlock;

// singleton.
BitMap*
BitMap::getInstance()
{
	BitMap* temp = 0;
	if (bm == 0) {
		temp = new BitMap();
	} else {
		return bm;
	}

	{
		// RAII
		std::lock_guard<std::mutex> lg(mlock);
		if (bm == 0) {
			bm = temp;
			temp = 0;
		} 
	}

	if (temp != 0) {
		delete temp;
	}

	return bm;
}

bool
BitMap::growSize(int s)
{
	std::lock_guard<std::mutex> lg(mlock);
	if (size >= s) {
		return false;
	}
	size = s;	
	bits.resize(size/8 + 1);
	
	return true;
}

void
BitMap::setBit(int p)
{
	assert(p < size);
	std::lock_guard<std::mutex> lg(mlock);
	bits[p/8] |= (1 << (p%8));
}

void
BitMap::unsetBit(int p)
{
	assert(p < size);
	std::lock_guard<std::mutex> lg(mlock);
	bits[p/8] &= ~(1 << (p%8));
}

bool
BitMap::isBitSet(int p)
{
	assert(p < size);
	std::lock_guard<std::mutex> lg(mlock);
	return (bits[p/8] & (1 << (p%8)));
}


int main()
{
	// test
	BitMap* bmp = BitMap::getInstance();
	if (bmp) {
		(void)bmp->growSize(16);

		bmp->setBit(2);
		cout << "Is bit pos 2 set? " <<
		   	bmp->isBitSet(2) << endl;
		bmp->unsetBit(2);
		cout << "Is bit pos 2 set? " <<
		   	bmp->isBitSet(2) << endl;
		bmp->setBit(3);
	}

	BitMap* bmp2 = BitMap::getInstance();
	if (bmp2) {
		// test singleton
		cout << "Is bit pos 3 set? " <<
		   	bmp2->isBitSet(3) << endl;
	}
}


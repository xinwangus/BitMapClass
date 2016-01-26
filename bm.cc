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
	mlock.lock();
	if (bm == 0) {
		bm = temp;
		temp = 0;
	} 
	mlock.unlock();

	if (temp != 0) {
		delete temp;
	}

	return bm;
}

bool
BitMap::growSize(int s)
{
	mlock.lock();
	if (size >= s) {
		mlock.unlock();
		return false;
	}
	size = s;	
	bits.resize(size/8 + 1);
	
	mlock.unlock();
	return true;
}

void
BitMap::setBit(int p)
{
	assert(p < size);
	bits[p/8] |= (1 << (p%8));
}

void
BitMap::unsetBit(int p)
{
	assert(p < size);
	bits[p/8] &= ~(1 << (p%8));
}

bool
BitMap::isBitSet(int p)
{
	assert(p < size);
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
		cout << "Is bit pos 3 set? " <<
		   	bmp2->isBitSet(3) << endl;
	}
}


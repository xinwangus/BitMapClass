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

// singleton.
BitMap*
BitMap::getInstance()
{
	// TODO locking.
	if (bm == 0) {
		bm = new BitMap();
	}
	return bm;
}

bool
BitMap::growSize(int s)
{
	if (size >= s) {
		return false;
	}
	size = s;	
	// TOD Why? to avoid seg fault.
	bits.resize(size/8 + 1);
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


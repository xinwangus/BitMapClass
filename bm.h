#include <iostream>
#include <vector>

using namespace std;

class
BitMap
{
public:
	~BitMap();
	// singleton
	static BitMap* getInstance();
	bool growSize(int s);

	void setBit(int p);
	void unsetBit(int p);
	bool isBitSet(int p);

private:
	BitMap();

	vector<char> bits;
	int size;

	static BitMap* bm;
	static std::mutex mlock;
};

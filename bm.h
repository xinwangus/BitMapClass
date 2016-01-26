#include <iostream>
#include <vector>

using namespace std;

struct
Data
{
	int bit_pos;
	string s;
};

class
BitMap
{
public:
	// singleton
	static BitMap* getInstance();
	bool growSize(int s);

	// int register(string& id);
	void setBit(int p);
	void unsetBit(int p);
	bool isBitSet(int p);

private:
	BitMap();
	~BitMap();

	vector<char> bits;
	vector<Data> data;
	int size;
	static BitMap* bm;
};

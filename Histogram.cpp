//
// Created by David Madden on 8/30/16.
//

#include "Histogram.h"

void Histogram::Read (istream& inFile) {
	char p2;
	inFile.get(p2);
	inFile.get(p2);
	//set to -1 as -1 is not a valid int
	int val;
	inFile >> width >> height >> maxVal;

	maxInts = width*height;
	//assign all bins in count to 0
	count.assign(maxInts,0);
	//while will run as long as inFile can extract into integer and inFile did not fail
	int allInts = 0;
	while (inFile >> val && !inFile.fail()) {
		//increase occurrence count for respective box
		Occurrence(val);
		//save value in vector
		allInts++;
	}
}

void Histogram::Occurrence(int value) {
	//truncate number so X/4 is integer not double
	int box = floor(value/4);
	//increase occurrence count for specific box
	count[box]++;
}

void Histogram::Normalize() {
	//assign all bins in normalized to 0
	normalized.reserve(64);

	double sum = 0;
	//finding sum of all bins
	for (int i = 0; i < 64; i++) {
		sum += count[i];
	}
	//normalizing bins by dividing by sum
	for (int i = 0; i < 64; i++) {
		normalized.push_back(count[i] / sum);
	}
}
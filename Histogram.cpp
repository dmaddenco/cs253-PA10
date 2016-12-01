//
// Created by David Madden on 8/30/16.
//

#include "Histogram.h"

bool Histogram::Read (istream& inFile) {
	char p2;
	inFile.get(p2);
	if (p2 == 'P') {
		inFile.get(p2);
		if (p2 != '2') return false;
	} else return false;
	//set to -1 as -1 is not a valid int
	int val = -1;
	inFile >> width >> height >> maxVal;

	if (width < 0 || height < 0) return false;
	if (width == 0 || height == 0) return false;
	if (width != 128 || height != 128) return false;
	if (maxVal != 255) return false;

	maxInts = width*height;
	//assign all bins in count to 0
	count.assign(maxInts,0);
	//while will run as long as inFile can extract into integer and inFile did not fail
	int allInts = 0;
	while (inFile >> val && !inFile.fail()) {
		//check if charRead is within range
		if (val < 0 || val > 255) {
			return false;
		}
		//increase occurrence count for respective box
		Occurrence(val);
		//save value in vector
		allInts++;
	}
	//error if file contained more than height*width ints
	if ((int)allInts != height*width) return false;

	//check if istream inFile failed
	if (inFile.fail() && !inFile.eof()) return false;

	//val will be -1 if inFile never found any numbers
	if (val == -1) return false;

	return true;
}

void Histogram::Occurrence(int value) {
	int box;
	//truncate number so X/4 is integer not double
	box = floor(value/4);
	//increase occurrence count for specific box
	count[box]++;
}

void Histogram::Normalize() {
	//assign all bins in normalized to 0
	normalized.reserve(64);
//	normalized.assign(64,0);
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
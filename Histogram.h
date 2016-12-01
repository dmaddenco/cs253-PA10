//
// Created by David Madden on 8/30/16.
//

#ifndef PA5_HISTOGRAM_H
#define PA5_HISTOGRAM_H

#include <math.h>
//using std::pow;
#include <algorithm>
using std::min;
#include <iostream>
using std::istream;
using std::ostream;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <cstring>
using std::strcmp;
#include <string>
using std::string;
#include <regex>
using std::regex;
using std::regex_match;

class Histogram {
public:
	//read file that is passed
	bool Read(istream& inFile);
	//will check what "bin" the value falls into and increase count
	void Occurrence(int value);

	//will normalize all counts
	void Normalize();

	//normalized bins
	vector<double> normalized;

protected:
	//occurrence count will be held for numbers in 0-255 range inclusively, all set to 0
	vector<int> count;
	//int that will be used for vector initialization
	int maxInts = 0;
	//to hold histogram width
	int width = 0;
	//to hold histogram height
	int height = 0;
	//to hold histogram max val
	int maxVal = 0;
};

#endif //PA5_HISTOGRAM_H

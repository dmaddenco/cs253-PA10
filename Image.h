//
// Created by David Madden on 10/5/16.
//

#ifndef CS253_PA5_IMAGE_H
#define CS253_PA5_IMAGE_H

#include "Histogram.h"

#include <fstream>
using std::ifstream;

class Image : public Histogram {
public:
	bool ReadFileNames(istream& inFile);	//read file names
	bool CreateHistograms();	//creates histograms
	void CreateImages();
	bool CheckN(int N);

	vector<string> files;	//file names that contain images
	vector<Histogram> normHistograms;	//holds all valid histograms
	vector<Image> images;

	string imageName;
	int imageClass;

	double compareScore = 0;
	int compareIndex = 0;
	int totalFiles = 0;

//	Histogram imageHist;
	vector<double> imageHist;
};

#endif //CS253_PA5_IMAGE_H

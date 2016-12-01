//
// Created by David Madden on 10/5/16.
//

#include "Image.h"

bool Image::ReadFileNames (istream& inFile) {
	string fileName;
	regex txt_regex("class[[:digit:]]+_[[:digit:]]+\\.pgm");
	while (inFile >> fileName) {
		if (!regex_match ( fileName.begin(), fileName.end(), txt_regex )) return false;	//ensure that file matches format 'class[0-9]+_[0-9]+.pgm'
		files.push_back(fileName);
		totalFiles++;
	}

	//check if istream inFile failed
	if (inFile.fail() && !inFile.eof()) return false;

	if (totalFiles < 2) return false;

	return true;
}

bool Image::CreateHistograms() {
	normHistograms.reserve(totalFiles);
	for (int i = 0; i < totalFiles; ++i) {
		Histogram histogram;
		ifstream fileToRead(files[i]);
		if (!histogram.Read(fileToRead)) return false;
		histogram.Normalize();
		normHistograms.push_back(histogram);
	}
	return true;
}

void Image::CreateImages() {
	images.reserve(normHistograms.size());
	for (int i = 0; i < (int) normHistograms.size(); ++i) {
		Image image;
		image.imageName = files[i];
		string stringImageClass = files[i];

		int found=files[i].find("_");
		image.imageClass = atoi(stringImageClass.substr(5,(found-5)).c_str());
		image.imageHist.reserve(64);
		image.imageHist = normHistograms[i].normalized;
		images.push_back(image);
	}
}

bool Image::CheckN(int N) {
	int count = 0;
	for (int i = 0; i < (int) images.size(); ++i) {
		if (N == images[i].imageClass) count++;
	}
	if (count == 0) return false;
	return true;
}

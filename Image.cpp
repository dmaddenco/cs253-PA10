//
// Created by David Madden on 10/5/16.
//

#include "Image.h"

void Image::ReadFileNames (istream& inFile) {
	string fileName;

	while (inFile >> fileName && !inFile.fail()) {
		files.push_back(fileName);
		totalFiles++;
	}
}

void Image::CreateHistograms() {
	normHistograms.reserve(totalFiles);
	for (int i = 0; i < totalFiles; ++i) {
		Histogram histogram;
		ifstream fileToRead(files[i]);
		histogram.Read(fileToRead);
		histogram.Normalize();
		normHistograms.push_back(histogram);
	}
	CreateImages();
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

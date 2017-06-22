//
// Created by David Madden on 11/22/16.
//

#include "Perceptron.h"

void Perceptron::GetClasses(vector<Image> images) {
    imagesInternal = images;
    for (int i = 0; i < (int) images.size(); ++i) {
        if (find(classes.begin(), classes.end(), images[i].imageClass) == classes.end()) {
            classes.push_back(images[i].imageClass);
        }
    }
}

void Perceptron::CreateNPerceptron() {
	perceptrons.reserve(classes.size());
	for (int m = 0; m < (int) classes.size(); ++m) {
		Perceptron p;
        p.w.reserve(64);
        p.w.assign(64, 0);
        b = 0; y = 0;
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < (int) imagesInternal.size(); ++j) {
				if (imagesInternal[j].imageClass == classes[m]) d = 1;
				else d = -1;
				y = ComputeY(b, p.w, imagesInternal[j].imageHist);
				for (int i = 0; i < (int) p.w.size(); ++i) {
					p.w[i] = p.w[i] + ((d - y) * imagesInternal[j].imageHist[i]);
				}
				b = UpdateB(y, b, d);
			}
		}
		p.b = b;
		perceptrons.push_back(p);
	}
}

double Perceptron::ComputeY(double b, vector<double> w, vector<double> hist) {
	double sum = 0;
	for (int j = 0; j < (int) hist.size(); ++j) {
		sum += (w[j]*hist[j]);
	}
	return sum + b;
}
//
// Created by David Madden on 11/22/16.
//

#include "Perceptron.h"

void Perceptron::CreateNPerceptron(vector<Image> images) {
	perceptrons.reserve(classes.size());
	for (int m = 0; m < (int) classes.size(); ++m) {
		Perceptron p;
		AssignW();
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < (int) images.size(); ++j) {
				if (images[j].imageClass == classes[m]) d = 1;
				else d = -1;
				y = ComputeY(b, w, images[j].imageHist);
				for (int i = 0; i < (int) w.size(); ++i) {
					w[i] = w[i] + ((d - y) * images[j].imageHist[i]);
				}
				b = UpdateB(y, b, d);
			}
		}
		p.w = w;
		p.b = b;
		perceptrons.push_back(p);
	}
}

bool Perceptron::GetClasses(vector<Image> images) {
	for (int i = 0; i < (int) images.size(); ++i) {
		if (find(classes.begin(), classes.end(), images[i].imageClass) == classes.end()) {
			classes.push_back(images[i].imageClass);
		}
	}
	if (classes.size() < 2) return false;
	return true;
}

double Perceptron::ComputeY(double b, vector<double> w, vector<double> hist) {
	double sum = 0;
	for (int j = 0; j < (int) hist.size(); ++j) {
		sum += (w[j]*hist[j]);
	}
	return sum + b;
}
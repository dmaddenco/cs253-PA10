//
// Created by David Madden on 11/22/16.
//

#ifndef CS253_PA9_PERCEPTRON_H
#define CS253_PA9_PERCEPTRON_H

#endif //CS253_PA9_PERCEPTRON_H

#include "Image.h"
#include "Histogram.h"

class Perceptron {
public:
	void GetClasses(vector<Image> images);
	void CreateNPerceptron(vector<Image> images);
	double ComputeY(double b, vector<double> w, vector<double> hist);
	inline double UpdateB(double y, double b, double d) { return (b + (d - y)); }

	double d, y, b;	//for perceptron
	vector<double> w;	//weights
	inline void AssignW() { w.reserve(64); w.assign(64, 0); b = 0; y = 0; }

	vector<int> classes;

	vector<Perceptron> perceptrons;
};
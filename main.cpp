/*
 * David Madden
 * CS253
 * maddendb@rams.colostate.edu"
 */

//code will be compiled using 'g++ -I. -Wall *.cpp -o PA1'
#include "Histogram.h"
#include "Image.h"
#include "Cluster.h"
//#include "Perceptron.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <fstream>
using std::ifstream;

int main(int argc, char* argv[]) {

	ifstream inFile1(argv[1]);
	ifstream inFile2(argv[2]);

	Image training, test;

	training.ReadFileNames(inFile1);
	test.ReadFileNames(inFile2);

	training.CreateHistograms();
	test.CreateHistograms();

	training.CreateImages();
	test.CreateImages();

	Perceptron perceptron;

	perceptron.GetClasses(training.images);

	Cluster cluster;

	perceptron.CreateNPerceptron(training.images);

	cluster.ClusterImages(test.images, atoi(argv[3]), perceptron.perceptrons);

	return 0;
}

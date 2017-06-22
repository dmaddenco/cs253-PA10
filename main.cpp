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

#include <thread>
using std::thread;

int main(int argc, char* argv[]) {

	ifstream inFile1(argv[1]);
	ifstream inFile2(argv[2]);

	Image training, test;
    Perceptron perceptron;
    Cluster cluster;

    training.ReadFileNames(inFile1);
    test.ReadFileNames(inFile2);

    thread tH1(&Image::CreateHistograms, &training);
	thread tH2(&Image::CreateHistograms, &test);

	tH2.join();
	tH1.join();

	thread tP1(&Perceptron::GetClasses, &perceptron, training.images);
	tP1.join();

    thread tP2(&Perceptron::CreateNPerceptron, &perceptron);
    tP2.join();

    cluster.ClusterImages(test.images, atoi(argv[3]), perceptron.perceptrons);

	return 0;
}

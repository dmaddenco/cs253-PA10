//
// Created by David Madden on 10/11/16.
//

#ifndef CS253_PA5_CLUSTER_H
#define CS253_PA5_CLUSTER_H

#include "Image.h"
#include "Histogram.h"
#include "Perceptron.h"

#include <set>
using std::multiset;

class Cluster : public Perceptron {
public:
	void ClusterImages(vector<Image>& images, int k, const vector<Perceptron>& perceptrons);
	void OutputCluster(const vector<Cluster>& clusters);

	vector<double> CreateAverageHist(const vector<Image>& images);
	vector<double> CreateNY(const vector<double>& histogram);

	void FixClusters(int clustersToGet, int numOfCurrentClusters);
	int MergeBestClusters(int indexC1, int indexC2);

	int FindBestClusters();
	double Similarity(const vector<double>& y1, const vector<double>& y2);

	vector<Image> clusterOfImages;

	vector<double> averageHist;
	vector<double> y;
	vector<Perceptron> ClusterPerceptron;
	vector<Cluster> oldClusters;
};

#endif //CS253_PA5_CLUSTER_H

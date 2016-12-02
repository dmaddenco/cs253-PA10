//
// Created by David Madden on 10/11/16.
//

#include "Cluster.h"
#include "Image.h"

void Cluster::ClusterImages(vector<Image>& images, int k, const vector<Perceptron>& perceptrons) {
	ClusterPerceptron = perceptrons;
	for (int i = 0; i < (int) images.size(); ++i) {
		Cluster cluster = Cluster();
		cluster.clusterOfImages.push_back(images[i]);	//create a cluster for each image
		cluster.averageHist = CreateAverageHist(cluster.clusterOfImages);	//create average histogram for each image
		cluster.y = CreateNY(cluster.averageHist);
		oldClusters.push_back(cluster);	//stores all clusters
	}
	if (k == (int) oldClusters.size()) {
		OutputCluster(oldClusters);	//no clustering to be done
	}
	else FixClusters(k, (int) oldClusters.size());

	OutputCluster(oldClusters);

}

void Cluster::FixClusters(int clustersToGet, int numOfCurrentClusters) {
	while (clustersToGet < (int) oldClusters.size()) {
		numOfCurrentClusters = FindBestClusters();
		FixClusters(clustersToGet, numOfCurrentClusters);	//recursive call until correct clusters obtained
	}
}

int Cluster::FindBestClusters() {
	double score = 0.0;
	int indexC1 = 0; int indexC2 = 0;	//used to find cluster pair later on
	for (int i = 0; i < (int) oldClusters.size(); ++i) {
		for (int j = 0; j < (int) oldClusters.size(); ++j) {
			if (i != j) {
                double compare = Similarity(oldClusters[i].y, oldClusters[j].y);
                if (score < compare) {
					score = compare;
					indexC1 = i;
					indexC2 = j;
				}
			}
		}
	}
	return MergeBestClusters(indexC1, indexC2);
}

int Cluster::MergeBestClusters(int indexC1, int indexC2) {

	for (int i = 0; i < (int) oldClusters[indexC2].clusterOfImages.size(); ++i) {
		oldClusters[indexC1].clusterOfImages.push_back(oldClusters[indexC2].clusterOfImages[i]);
	}
	oldClusters[indexC1].averageHist = CreateAverageHist(oldClusters[indexC1].clusterOfImages);
	oldClusters[indexC1].y = CreateNY(oldClusters[indexC1].averageHist);
	oldClusters.erase(oldClusters.begin()+indexC2);
	return (int) oldClusters.size();
}

double Cluster::Similarity(const vector<double>& y1, const vector<double>& y2) {
	double epsilon = 0.001;	//if denominator of similarity == 0, add epsilon
	double similarity = 0;
	for (int i = 0; i < (int) y1.size(); ++i) {
		double denominator = (y1[i] - y2[i]);
//		if (denominator == 0) denominator += epsilon;
		denominator+=epsilon;
		similarity += (1/((denominator*denominator)));
	}
	return similarity;
}

void Cluster::OutputCluster(const vector<Cluster>& clusters) {
	for (int i = 0; i < (int) clusters.size(); ++i) {
		for (int j = 0; j < (int) clusters[i].clusterOfImages.size(); ++j) {
			cout<<clusters[i].clusterOfImages[j].imageName<<" ";
		}
		cout<<endl;
	}
}

vector<double> Cluster::CreateNY(const vector<double>& histogram) {
	double internalY = 0;
	vector<double> y;
	y.reserve(ClusterPerceptron.size());
	for (int i = 0; i < (int) ClusterPerceptron.size(); ++i) {
		internalY = ComputeY(ClusterPerceptron[i].b, ClusterPerceptron[i].w, histogram);
		y.push_back(internalY);
	}
	return y;
}

vector<double> Cluster::CreateAverageHist(const vector<Image>& images) {
	vector<double> average;
	average.reserve(64);
	average.assign(64,0);
	for (int i = 0; i < (int) images.size(); ++i) {
		for (int j = 0; j < (int) images[i].imageHist.size(); ++j) {
			average[j] += images[i].imageHist[j];
		}
	}
	for (int k = 0; k < (int) average.size(); ++k) {
		average[k] /= images.size();
	}
	return average;
}
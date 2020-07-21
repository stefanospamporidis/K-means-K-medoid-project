//
//  CubeUtils.hpp
//  project1
//
//  Created by <author> on 08/10/2019.
//
//

#ifndef CubeUtils_hpp
#define CubeUtils_hpp

#define INFTY std::numeric_limits<int>::max()
#define THRESHOLD 10
using namespace  std ;

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include "../include/Database.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <utility>
#include "../include/Hypercube.hpp"

struct ParametersCube
{
	string input_file;
	string query_file;
	int K;
	int M;
	int probes ;
	string output_file;
	float radius;

};


class CubeUtils {
private:
	int hits ; // number of correct results of nn
	int misses ; // number of incorrect results of nn
	long errorsum ; // sum of error
	double maxAF ;
	double sumAF ;
    ParametersCube params ;
	Hypercube *cube ;
	Database *db ; // Database containing input points
	Database *qs ; // Database containing query points
	std::pair<int,Point *> nn(Point *);
	std::pair<int,Point *> linear_search(Point *); // Finds the nearest neighbour using a linear scan of the input points .
	void calculateAverageDistance(void);
public:
    CubeUtils();
    void getArgs(int ,char ** );
    void printArgs();
    void getPoints();
	void initHypercube();
	void parseQueries();
	void runQueries();
    ~CubeUtils();
protected:

};


#endif /* CubeUtils_hpp */

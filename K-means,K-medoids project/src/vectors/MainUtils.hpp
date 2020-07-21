//
//  MainUtils.hpp
//  project1
//
//  Created by <author> on 08/10/2019.
//
//

#ifndef MainUtils_hpp
#define MainUtils_hpp

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
#include "../include/Hashtable.h"

struct Parameters
{
	string input_file;
	string query_file;
	int K;
	int L;
	string output_file;
	float radius;

};


class MainUtils {
private:
	int hits ; // number of correct results of nn
	int misses ; // number of incorrect results of nn
	long errorsum ; // sum of error
	double maxAF ;
	double sumAF ;
    Parameters params ;
	std::vector<Hash *> hashtables;
	Database *db ; // Database containing input points
	Database *qs ; // Database containing query points
	std::pair<int,Point *> nn(Point *);
	std::pair<int,Point *> linear_search(Point *); // Finds the nearest neighbour using a linear scan of the input points .
	void calculateAverageDistance(void);
public:
    MainUtils();
    void getArgs(int ,char ** );
    void printArgs();
    void getPoints();
	void initHTS();
	void parseQueries();
	void runQueries();
    ~MainUtils();
protected:

};


#endif /* MainUtils_hpp */

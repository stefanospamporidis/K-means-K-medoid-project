//
//  CurveGridMainUtils.hpp
//  project1
//
//  Created by <author> on 19/10/2019.
//
//

#ifndef CurveGridMainUtils_hpp
#define CurveGridMainUtils_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Parser.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include "CurveDatabase.hpp"
#include "../include/Database.hpp"

#ifdef HASH_TABLE
#include "../include/Hashtable.h"
#endif

#ifdef HYPERCUBE
#include "../include/Hypercube.hpp"
#endif

#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <utility>
#include "Grid.hpp"



struct CurveGridParameters
{
	std::string input_file;
	std::string query_file;
	int K;
	#ifdef HYPERCUBE
	int M ;
	int probes ;
	#endif
	int L;
	std::string output_file;
	float radius;

};


class CurveGridMainUtils {
private:
	int hits ; // number of correct results of nn
	int misses ; // number of incorrect results of nn
	long errorsum ; // sum of error
	double maxAF ;
	double sumAF ;
	int maxInpCurveSize ; //
    CurveGridParameters params ;
    Parser *parser ;
	Parser *qparser ; // Query parser
	//std::vector<Hash *> hashtables;
	CurveDatabase *db ; // Database containing input points
	CurveDatabase *qs ; // Database containing query points

	Database *dbk ; // db containing the concated curves / points
	Database *qsk ; // db containing the concated curves / points queries
	#ifdef HASH_TABLE
	Hash *ht ; // Hashtable for doing lsh
	#endif
	#ifdef HYPERCUBE
	Hypercube *ht ;
	#endif
	//std::pair<int,Point *> nn(Point *);
	//std::pair<int,Point *> linear_search(Point *); // Finds the nearest neighbour using a linear scan of the input points .
	std::vector<Grid *> grids;
	std::pair<int,Curve *> linear_search(Curve *q);
	void calculateAverageDistance(void);
	std::pair<int,Curve *> nn(Curve *q);

public:
    CurveGridMainUtils();
    void getArgs(int ,char ** );
    void printArgs();
    void getPoints();
	void initGrids();
	void initHTS();
	void parseQueries();
	void runQueries();
    ~CurveGridMainUtils();
protected:

};


#endif /* CurveGridMainUtils_hpp */

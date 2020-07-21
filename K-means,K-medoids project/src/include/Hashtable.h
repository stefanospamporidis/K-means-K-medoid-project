#ifndef HASHTABLE_H
#define HASHTABLE_H

#define INFTY std::numeric_limits<int>::max()
#define W_CONST 3000

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include <utility>
#include <limits>
#include <cmath>
#include <ctime>
#include <stdint.h>
#include "Database.hpp"

using namespace std;



class Hash
{
private :
	Database *db ;
	int uniform_distribution(int ,int ); // Produces random , uniformly distributed number in the interval
	unsigned int calculate_mod(unsigned int m,int power,unsigned int M,int a) ;
	unsigned int m ;

public:

	vector< vector<Point *> * > htable; //O hashtable 8a krataei mesa tou Points pou pirame apo to input kai apo8ikeusame sto database
	vector< Point* > start_points;
	int k,hsize,d; //painrei apo tis parametrous to k pou einai o ari8mos twn starting points pou 8a xrisimopoihsoume,kai to radius pou to 8eloume gia to w
	float radius,w;
	void printBuckets(void);
    Hash(int k,float rad,int size,int d, Database *);  // Constructor

  	~Hash(); //Destructor

  	void create_Starting_Points();

  	void insert_Database(void);

  	std::pair<int,Point *> search_query_neighbour(Point *,int );

  	unsigned int g(Point *);

  	unsigned int h(Point *,Point *);

  	int getmax(Point &);

  	unsigned int mod_Calculator(unsigned int m,unsigned int power,unsigned int M,int ai);

  	static int Manhattan_Distance(Point * q,Point * x);
};



#endif

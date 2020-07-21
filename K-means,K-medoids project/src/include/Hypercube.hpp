//
//  Hypercube.hpp
//  project1
//
//  Created by <author> on 17/10/2019.
//
//

#ifndef Hypercube_hpp
#define Hypercube_hpp

#include <stdio.h>

#include "Database.hpp"
#include "Hashtable.h"
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <random>

#define CUBE_THRESHOLD 3000

class Hypercube {
private:
    int probes ; // Number of probes performed
    int d_og ; // The original dimension of our data
    int d_new ; // The dimension our data is projected to
    int M ; // number of points searched
    std::vector<Hash *> gd; // The d' functions used to map the data to ints
    std::map<unsigned int,std::vector<Point *>> projections; // Store the point with its associated [f_0,f_1 ...] int storing the 01 sequence .
    std::vector<std::map<unsigned int,int>> fs; // The d' function used to map the g to {0,1} uniformly
    std::vector<std::uniform_int_distribution<int>> dist;
    std::default_random_engine generator;
    Database * db ; // Database of input points
    std::vector<unsigned int> calculate_hamming_neighbors(unsigned int); /// finds the neighbors of the vertice by hamming distance
public:
    Hypercube(Database *,int,int,int ); // The dimension that we project the data to
    std::pair<int,Point *> nn(Point *) ; // Find the nearest neighbour
    static int Hamming_Distance(unsigned int ,unsigned int ,int ); // Calculates the hamming distance of 2 unsigned int with the number stored in first n bits
    static int bitCount2(int ); // Counts the number of 1s in an int

    ~Hypercube();
protected:

};


#endif /* Hypercube_hpp */

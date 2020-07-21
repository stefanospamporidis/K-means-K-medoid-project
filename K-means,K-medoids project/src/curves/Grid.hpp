//
//  Grid.hpp
//  project1
//
//  Created by <author> on 21/10/2019.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "Curve.hpp"

#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>
#include <time.h>


class Grid {
private:
    int d ;
    double delta ;
    std::vector<double> t; // Real vector t that shifts the inputs
    std::default_random_engine generator;
    std::uniform_real_distribution<double> t_dist; // Generates random real values for t
    coordinates * snap(coordinates *) ; // snap point to curve

public:
    Grid(int d,double delta); // d is the dimenion of each point of the curve , delta is a number given by the user
    Curve * snapCurve(Curve *); // snaps entire curve
    ~Grid();
protected:

};


#endif /* Grid_hpp */

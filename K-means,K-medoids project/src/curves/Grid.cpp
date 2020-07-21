//
//  Grid.cpp
//  project1
//
//  Created by <author> on 21/10/2019.
//
//

#include "Grid.hpp"

Grid::Grid(int d ,double delta) : d(d) , delta(delta) , t_dist(0,d) {
    this->generator.seed(time(NULL));
    // We generate the random values for the t vec in [0,d)^d
    for (size_t i = 0; i < d; i++) {
        t.push_back(t_dist(this->generator));
        //std::cout << t[i] << std::endl ;
    }
}
int min4(double a , double b ,double c ,double d) {
    double data[] = {a,b,c,d};
    double min = INFINITY ;
    int index = -1 ;
    for (size_t i = 0; i < 4; i++) {
        if (data[i] < min) {
            index = i ;
            min = data[i];
        }
    }
    return index ;
}
// Snap the point q to the correct grid
// We have to find the a_1 , a_2 that minimize the following function
// |a_1 * delta + t_1 - q_1 | + | a_2 * delta + t_2 - q_2|
// We have that the equation is minimized when
// a_1 = (x_1 - t_1) / delta  , a_2 (x_2 - t_2) / delta
// a_1,a_2 are integers so we take the floor and ceiling functions
// a_1_1 = floor(a_1) , a_1_2 = ceiling(a_1) , a_2_1 = floor(a_2) , a_2_2 = ceiling(a_2)
// so we have 4 combinations . We pick the minimum
coordinates * Grid::snap(coordinates *q) {
    double a_1 = abs(q->x - t[0]) / (double) delta ;
    double a_2 = abs(q->y - t[1]) / (double) delta ;
    int a_1_1 = floor(a_1);
    int a_1_2 = ceil(a_1);
    int a_2_1 = floor(a_2);
    int a_2_2 = ceil(a_2);
    double a11a21 = (a_1_1*delta - q->x) + abs(a_2_1*delta - q->y);
    double a12a21 = (a_1_2*delta - q->x) + abs(a_2_1*delta - q->y);
    double a11a22 = (a_1_1*delta - q->x) + abs(a_2_2*delta - q->y);
    double a12a22 = (a_1_2*delta - q->x) + abs(a_2_2*delta - q->y);
    int index = min4(a11a21,a12a21,a11a22,a12a22);
    coordinates *m ;
    switch (index) {
        case 1:
            m = new coordinates(a_1_1*delta,a_2_1*delta);
            break ;
        case 2:
            m = new coordinates(a_1_2*delta,a_2_1*delta);
            break ;
        case 3:
            m = new coordinates(a_1_1*delta,a_2_2*delta);
            break ;
        case 4:
            m = new coordinates(a_1_2*delta,a_2_2*delta);
            break ;

    }
    return m ;
}
Curve * Grid::snapCurve(Curve *q) {
    Curve *l = new Curve(q->getId(),q->getSize()); // The curve we return
    coordinates *prev = this->snap(q->getPoint(0)); // We store the previous coordinates and check if they are equal
    l->addPoint(prev->x,prev->y);

    for (size_t i = 1 ; i < q->getSize(); i++) {
        coordinates * m = this->snap(q->getPoint(i));
        // duplicate so we dont add it
        if ((*m) == (*prev)) {
            delete prev ;
            prev = m ;
            continue ;
        }
        l->addPoint(m->x,m->y);
        delete prev ;
        prev = m ;
    }
    delete prev ;
    return l ;
}
Grid::~Grid() {
}

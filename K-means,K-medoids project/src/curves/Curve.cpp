//
//  Curve.cpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#include "Curve.hpp"

Curve::Curve(std::string id,int size) : id(id) {
    //points.reserve(size);
}
void Curve::addPoint(double x,double y) {
    coordinates *m = new coordinates(x,y);
    points.push_back(m);
}
std::string Curve::getId(void) {
    return id ;
}
int Curve::getSize(void)  {
    return points.size();
}
coordinates * Curve::getPoint(int index) {
    return points[index];
}
double min3(double x ,double y , double z) {
    if (x < y) {
        if (x < z) {
            return x ;
        } else {
            return z ;
        }
    } else if (y < z){
        return y ;
    }
}
// See
// https://en.wikipedia.org/wiki/Dynamic_time_warping
double Curve::dtwDistance(Curve  *q){
    int n = this->getSize();
    int m = q->getSize() ;
    double DTW[n+1][m+1] ; // Array with distances
    for (size_t i = 0; i < n+1; i++) {
        for (size_t j = 0; j < m+1; j++) {
            DTW[i][j] = INFINITY ;
        }
    }
    DTW[0][0] = 0 ;
    for (size_t i = 1; i < n+1; i++) {
        for (size_t j = 1; j < m+1; j++) {
            double cost = (q->getPoint(j-1))->dist(*(points[i-1]));
            DTW[i][j] = cost + min3(DTW[i-1][j],DTW[i][j-1],DTW[i-1][j-1]);
        }
    }
    return DTW[n][m];
}
std::vector<std::string> Curve::concatData(int padding) {
    double max = -1 * INFINITY ;
    std::vector<std::string> v;
    for (size_t i = 0; i < points.size(); i++) {
        std::string crd_s_1 ;
        std::string crd_s_2 ;
        double x = points[i]->x ;
        double y = points[i]->y ;

        if (x > max) {
            max = x ;
        }
        if (y > max) {
            max = y ;
        }

        crd_s_1 = std::to_string(x);
        crd_s_2 = std::to_string(y);
        v.push_back(crd_s_1);
        v.push_back(crd_s_2);
    }
    std::string maxS = std::to_string(max);
    // fill remaining positions with the max value of coordinates
    int ssize = v.size() ;
    for (size_t i = 0; i < (padding - ssize); i++) {
        v.push_back(maxS);
    }
    return v ;
}

Curve::~Curve() {
    for (size_t i = 0; i < points.size(); i++) {
        delete  points[i];
    }
}

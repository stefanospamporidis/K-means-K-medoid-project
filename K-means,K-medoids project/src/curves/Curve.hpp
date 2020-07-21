//
//  Curve.hpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#ifndef Curve_hpp
#define Curve_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

struct coordinates {
    double x ;
    double y ;
    coordinates(double x,double y) : x(x) , y(y) {}
    double dist(coordinates p) {
        return sqrt((abs(p.x - x)*abs(p.x - x) + abs(p.y - y)*abs(p.y - y))) ; // euclidian distance
        // see https://eclass.uoa.gr/modules/forum/viewtopic.php?course=DI352&topic=22350&forum=33439
    }
    friend bool operator==(const coordinates& lhs, const coordinates& rhs){
        return (lhs.x == rhs.x) && (lhs.y == rhs.y) ;
    }
    ~coordinates() {}
};


class Curve {
private:
    std::string id ;
    std::vector<coordinates *> points; // a vector containing all the coordinates of the curve
public:
    Curve(std::string ,int );
    void addPoint(double ,double );
    coordinates * getPoint(int );
    std::string getId(void);
    int getSize(void); // Returns the size of the curve
    double dtwDistance(Curve *); // Calculates  the distance of this curve with the one provided by the user
    std::vector<std::string> concatData(int);

    ~Curve();
protected:

};


#endif /* Curve_hpp */

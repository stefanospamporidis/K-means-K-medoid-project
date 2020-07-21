//
//  CurveDatabase.hpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#ifndef CurveDatabase_hpp
#define CurveDatabase_hpp

#include "Curve.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>

class CurveDatabase {
private:
    std::vector<Curve *> entries;
public:
    CurveDatabase();
    int getSize() { return entries.size();}
    //void addCurve(std::string , int ); // Add curve with id and number of points to db
    void addCurve(std::string,int,std::vector<std::pair<double,double>>);
    void addPoint(std::string ,double ,double ); // Add a point to the curve
    int getMaxLenCurve(void) ; // Returns number of points in the largest curve
    Curve * getCurve(int ); // Get curve at index
    ~CurveDatabase();
protected:

};


#endif /* CurveDatabase_hpp */

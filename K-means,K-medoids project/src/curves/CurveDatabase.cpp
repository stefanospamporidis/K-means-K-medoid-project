//
//  CurveDatabase.cpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#include "CurveDatabase.hpp"

CurveDatabase::CurveDatabase()  {}
void CurveDatabase::addPoint(std::string qId,double x,double y) {
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i]->getId() == qId) {
            entries[i]->addPoint(x,y);
            break ;
        }
    }
}
void CurveDatabase::addCurve(std::string id,int npoints ,std::vector<std::pair<double,double>> points) {
    Curve *c = new Curve(id,npoints);
    for (size_t i = 0; i < points.size(); i++) {
        c->addPoint(points[i].first,points[i].second);
    }
    entries.push_back(c);

}
int CurveDatabase::getMaxLenCurve(void) {
    int max = -1 ;
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i]->getSize() > max) {
            max = entries[i]->getSize();
        }
    }
    return max ;
}
Curve * CurveDatabase::getCurve(int index) {
    return entries[index];
}
CurveDatabase::~CurveDatabase() {
    for (size_t i = 0; i < entries.size(); i++) {
        delete entries[i];
    }
}

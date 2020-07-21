//
//  Database.hpp
//  project1
//
//  Created by <author> on 08/10/2019.
//
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <utility>

using namespace std ;


class Point{  //edw apo8ikeuetai to ka8e simeio

public:
	string itemId;
	vector<float> array;

	friend ostream& operator<<(ostream& os, const Point& pt) {
		os << "[ " << pt.itemId << "|" ;
	    for (size_t i = 0; i < pt.array.size(); i++) {
	        os << pt.array[i] << " " ;
	    }
	    os << "]\n" ;
		return os ;
	}


};

class Database{
	std::vector<Point *> database;

public:
	Database();
	void addPoint(Point *);
	void addPoint(string ,vector<string> ); // Receives data from the
	// csv parser and adds them to the database
	void cleanUp();
	Point *operator[] (int);
	int size(void) ; // Size of the data
	int dimensions(void) ; // Dimensions of the data
	void print(void);
	~Database();

};


#endif /* Database_hpp */

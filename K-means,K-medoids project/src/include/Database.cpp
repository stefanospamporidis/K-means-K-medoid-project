//
//  Database.cpp
//  project1
//
//  Created by <author> on 08/10/2019.
//
//

#include "Database.hpp"

Database::Database()  {}
void Database::addPoint(Point *p){
	//database.push_back(p);
}


void Database::cleanUp(){ //adeiazei to eswteriko tou antikeimenou kai meta diagrafei to antikeimeno
	//int i;
	//for (i=0;i<database.size();i++){
	//	delete database[i];
	//}
	//database.clear();
}
void Database::addPoint(string id,vector<string> values) {
    class Point *newPoint = new Point ;
    newPoint->itemId = id ;
    for (size_t i = 0; i < values.size(); i++) {
        float v = stof(values[i]);
        newPoint->array.push_back(v);
    }
    database.push_back(newPoint);
}
Point *Database::operator[] (int index) {
    return database[index] ;
}
int Database::size(void) {
    return database.size();
}
int Database::dimensions(void) {
    auto it = database.begin();
    return (*it)->array.size();
}
void Database::print(void) {
    for (size_t i = 0; i < database.size(); i++) {
        cout << ' ' << *database[i] ;
    }
}
Database::~Database(){
	int i;
	for (auto it=database.begin(); it!=database.end(); ++it) {
		//std::cout << ' ' << *(it);
		delete (*it) ;
	}
	/*
	for (i=0;i<database.size();i++){

        std::cout << *database[i];
		delete database[i];
	}
	*/
}

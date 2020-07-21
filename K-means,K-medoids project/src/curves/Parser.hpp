//
//  Parser.hpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CurveDatabase.hpp"


// Parses the files with the curve data
class Parser {
private:
    std::string inputfile ;
public:
    Parser(std::string ,CurveDatabase *); // Received the input file
    void fillDB(CurveDatabase *) ; // Gets the database and adds all the curves
    ~Parser();
protected:

};


#endif /* Parser_hpp */

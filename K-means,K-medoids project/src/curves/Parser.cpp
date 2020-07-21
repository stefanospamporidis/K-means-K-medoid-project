//
//  Parser.cpp
//  project1
//
//  Created by <author> on 18/10/2019.
//
//

#include "Parser.hpp"

Parser::Parser(std::string inputfile,CurveDatabase *db) : inputfile(inputfile) {
    std::cout << "Inserting Database" << '\n';
    std::ifstream file(inputfile);
    //std::istringstream str(file);

    while (!file.eof()) {
        std::vector<std::string>    m_data;

        std::string         line;
        std::getline(file, line);

        std::stringstream   lineStream(line);
        std::string         cell;
        std::string id ;
        m_data.clear();
        std::getline(lineStream, id, '\t') ; // Get id of line
        std::getline(lineStream, cell, '\t') ; // Get number of points
        if (id.empty() || cell.empty()) {
            break ;
        }
        int npoints = stoi(cell);
        //db->addCurve(id,npoints);
        //std::cout << "Inserting line with id " << id << '\n';
        // now we retrieve every point of the curve
        std::vector<std::pair<double,double>> temp;
        std::pair<double,double> p ;
        while(std::getline(lineStream, cell, ')'))
        {
            std::string point1 ;
            std::string point2 ;

            cell.erase(cell.begin()); // Remove '('
            cell.erase(cell.begin()); // Remove '('
            std::stringstream   cellStream(cell);
            //std::cout << cell << '\n';
            std::getline(cellStream,point1,',');
            std::getline(cellStream,point2);
            p.first  = std::stod(point1);
            p.second = std::stod(point2);
            temp.push_back(p);
        }
        db->addCurve(id,npoints,temp);
        // This checks for a trailing comma with no data after it.
        //if (!lineStream && cell.empty())
        //{
            // If there was a trailing comma then add an empty element.
        //    m_data.push_back("");
        //}
        // We have reached the eof
        if (m_data.size() == 0) {
            continue ;
        }
        // We have stored the data in a vector of strings so we have to add them to our database
        //m_data.erase(m_data.begin());
        if (m_data[m_data.size() - 1].compare("\r") == 0) {
            m_data.pop_back() ;
            //std::cout << "is r" << std::endl ;
        }
        //m_data.pop_back();
        //db->addPoint(id,m_data);

        //std::cout << std::endl ;
    }

}
Parser::~Parser() {}

//
//  Hypercube.cpp
//  project1
//
//  Created by <author> on 17/10/2019.
//
//

#include "Hypercube.hpp"

Hypercube::Hypercube(Database *db,int d,int probes,int M) : d_new(d) , probes(probes) , M(M) {
    db = db ;
    d_og = db->dimensions();
    for (size_t i = 0; i < d_new; i++) {
        Hash * gh = new Hash(4,1,db->size()  / 8,d_og,db);
        std::cout << "Init g_" << i << std::endl ;
        gd.push_back(gh);
        dist.push_back(std::uniform_int_distribution<int> (0,1));
        fs.push_back(std::map<unsigned int,int> ());
    }
    std::cout << "Inserting points to cube " << std::endl ;
    for (size_t i = 0; i < db->size(); i++) {
        //std::cout << "point " << i << std::endl ;
        unsigned int pr = 0 ;
        for (size_t j = 0; j < gd.size(); j++) {

            unsigned int g = gd[j]->g(db->operator[](i));
            auto fsit = fs[j].find(g);
            int f ;
            if (fsit == fs[j].end()) {
                f = dist[j](this->generator) ; // Produce random number in {0,1}
                fs[j].insert({g,f});
            } else {
                f = fsit->second ;
            }
            pr = pr << 1 ;
            pr += f ;
        }

        auto it = projections.find(pr) ;
        if (it == projections.end()) {
            // key not found so we insert it with a new vector point
            std::vector<Point *> points;
            points.push_back(db->operator[](i));
            projections.insert({pr,points});
        } else {
            it->second.push_back(db->operator[](i));
        }

    }
    std::cout << "Finished inserting points to cube " << std::endl ;

}
// found at https://codingforspeed.com/a-faster-approach-to-count-set-bits-in-a-32-bit-integer/
int Hypercube::bitCount2(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}
int Hypercube::Hamming_Distance(unsigned int a ,unsigned int b,int n) {
    unsigned int r = 0 ;
    for (size_t i = 0; i < n; i++) {
        r = ((r) << 1) + 1 ;
    }
    // We eliminate the trailing bits that we dont need
    unsigned int an = a & r ;
    unsigned int bn = b & r ;
    unsigned int x = an ^ bn ; // We xor the two numbers
    // the hamminig distance is the number of 1s in the result
    return Hypercube::bitCount2(x);
}
std::vector<unsigned int> Hypercube::calculate_hamming_neighbors(unsigned int q) {
    std::vector<unsigned int> ret;
    std::map<int, std::vector<unsigned int>> mymap;
    unsigned int r = 1 ;
    for (size_t i = 0; i < d_new; i++) {
        r = r << 1 ;
    }
    r = r - 1 ; // We get the maximum number in a int with d' number of bits
    for (unsigned i = 0; i <= r; i++) {
        int distance = Hypercube::Hamming_Distance(q,i,d_new);
        auto it = mymap.find(distance);
        if (it == mymap.end()) {
            std::vector<unsigned int> k ;
            k.push_back(i);
            mymap.insert({distance,k});
        }
        else {
            it->second.push_back(i);
        }
    }
    for (size_t p = 0,c = 0; p <= d_new , c < probes; p++) {
        auto it = mymap.find(p); // Get all int with distance 1,2,...
        if (it == mymap.end()) {
            exit(1);
        }
        else {
            auto hn = it->second;
            for (size_t i = 0; i < hn.size() , c < probes ; i++) {
                ret.push_back(hn[i]);
                c++;
            }
        }
    }
    return ret ;
}

std::pair<int,Point *> Hypercube::nn(Point *q) {
    int min = INFTY ;
    Point *b = NULL ;
    unsigned int pr = 0 ;
    for (size_t j = 0; j < gd.size(); j++) {
        unsigned int g = gd[j]->g(q);
        auto fsit = fs[j].find(g);
        int f ;
        if (fsit == fs[j].end()) {
            f = dist[j](this->generator) ; // Produce random number in {0,1}
            //fs[j].insert({g,f});
        } else {
            f = fsit->second ;
        }
        pr = pr << 1 ;
        pr += f ;
    }
    // we calculate the hamming neighbors and then probe them
    auto neighbors = calculate_hamming_neighbors(pr);
    for (size_t i = 0; i < neighbors.size(); i++) {
        auto it = projections.find(neighbors[i]) ;
        if (it == projections.end()) {
            // key not found so we insert it with a new vector point
        } else {
            auto searchps = it->second ;
            for (size_t j = 0; j < searchps.size(); j++) {
                if (j == M) {
                    break ;
                }
                auto r = Hash::Manhattan_Distance(q,searchps[j]);
                if (r < min) {
                    min = r ;
                    b = searchps[j] ;
                }
            }
        }
    }
    return std::pair<int,Point *> (min,b);



}
Hypercube::~Hypercube() {
    for (size_t i = 0; i < gd.size(); i++) {
        delete gd[i];
    }
}

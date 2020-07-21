//
//  CurveGridCurveGridCurveGridMainUtils.cpp
//  project1
//
//  Created by <author> on 19/10/2019.
//
//

#include "CurveGridMainUtils.hpp"

CurveGridMainUtils::CurveGridMainUtils()  {
    db = new CurveDatabase();
    qs = new CurveDatabase();
    dbk = new Database() ;
    qsk = new Database() ;
    errorsum = 0 ;
    hits = 0 ;
    misses = 0 ;
    maxAF = -1 ;
    sumAF = 0 ;
}
CurveGridMainUtils::~CurveGridMainUtils() {
    //db->print();
    //qs->print();
    delete db ;
    delete qs ;
    delete dbk ;
    delete qsk ;
    if (parser != NULL) {
        delete parser ;
    }
    for (size_t i = 0; i < grids.size(); i++) {
        delete grids[i] ;
    }
    delete ht ;
    //for (size_t i = 0; i < hashtables.size(); i++) {
    //    delete hashtables[i] ;
    //}
}

void CurveGridMainUtils::getArgs(int argc,char **argv) {
    /* Parse cmd line parameters using getopts
     * Modified example found at :
     * https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html#Getopt-Long-Option-Example
     */
    int c ;
    while (1) {
        static struct option long_options[] =
        {
            /* These options don’t set a flag.
            We distinguish them by their indices. */
            {"d"         , required_argument , 0 , 'd'},
            {"q"        , required_argument , 0 , 'q'},
            #ifdef HASH_TABLE
            {"k_vec"    , required_argument , 0 , 'k'},
            #endif
            #ifdef HYPERCUBE
            {"k_hypercube"    , required_argument , 0 , 'k'},
            {"M",required_argument,0,'M'},
            {"probes" , required_argument , 0 ,'p'},
            #endif
            {"L_grid"           , optional_argument , 0 , 'L'},
            {"o"          , required_argument , 0 , 'o'},
            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        #ifdef HASH_TABLE
        c = getopt_long (argc, argv, "d:q:k:L::o:",
                long_options, &option_index);
        #endif
        #ifdef HYPERCUBE
        c = getopt_long (argc, argv, "d:q:k:M:p:L::o:",
                long_options, &option_index);
        #endif

        /* Detect the end of the options. */
        if (c == -1)
            break;
        switch (c) {
            case 'd':
                params.input_file.insert(0,optarg);
                break;
            case 'q':
                params.query_file.insert(0,optarg);
                break;
            case 'k':
                params.K = atoi(optarg);
                break;
            #ifdef HYPERCUBE
            case 'M' :
                params.M = atoi(optarg) ;
                break ;
            case 'p' :
                params.probes = atoi(optarg) ;
                break ;
            #endif
            case 'L':
                if (optarg) {
                    params.L = atoi(optarg);
                }else
                    params.L = 4 ;
                break;
            case 'o':
                params.output_file.insert(0,optarg);
                break;
            case '?':
            /* getopt_long already printed an error message. */
                break;
            default:
                abort ();
        }
    }
}
void CurveGridMainUtils::printArgs(void) {
    std::cout << "Input File " << params.input_file << std::endl ;
    std::cout << "Query File " << params.query_file << std::endl ;
    std::cout << "K " << params.K << std::endl ;
    #ifdef HYPERCUBE
    std::cout << "M " << params.M << std::endl ;
    std::cout << "probes " << params.probes << std::endl ;
    #endif
    std::cout << "L " << params.L << std::endl ;
    std::cout << "Output File " << params.output_file << std::endl ;

}
// Used code from https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
void CurveGridMainUtils::getPoints(){
    parser = new Parser(params.input_file,db);
}
void CurveGridMainUtils::initGrids(void) {
    std::cout << "Initiating Grids" << '\n';
    for (size_t i = 0; i < params.L; i++) {
        Grid * m = new Grid(2,0.0001); // Create grid and push back to grids
        grids.push_back(m);
    }
    maxInpCurveSize = db->getMaxLenCurve() ;
    int len = 2*maxInpCurveSize;
    std::cout << "Mapping points" << '\n';
    for (size_t i = 0; i < db->getSize(); i++) {
        Curve *c = db->getCurve(i);
        for (size_t j = 0; j < grids.size(); j++) {
            Curve *snapped = grids[j]->snapCurve(c);
            std::vector<string> curveData = snapped->concatData(len);
            dbk->addPoint(c->getId(),curveData);
            delete snapped ;
        }
    }
    std::cout << "Inserting database to hashtable" << '\n';
    std::cout << "Db size = " << dbk->size() << '\n';
    
    #ifdef HASH_TABLE
    ht = new Hash(params.K,1,dbk->size() / 16 , dbk->dimensions(),dbk);
    #endif
    #ifdef HYPERCUBE
    ht = new Hypercube(dbk,params.K,params.probes,params.M);
    #endif
}
void CurveGridMainUtils::initHTS(void) {
    #ifdef HASH_TABLE
    ht->insert_Database();
    ht->printBuckets();
    #endif
}
void CurveGridMainUtils::parseQueries(void) {
    std::cout << "Parsed queries" << '\n';
    qparser = new Parser(params.query_file,qs);
    int len = 2*maxInpCurveSize;
    std::cout << "Mapping query points" << '\n';
    for (size_t i = 0; i < qs->getSize(); i++) {
        Curve *c = qs->getCurve(i);
        for (size_t j = 0; j < grids.size(); j++) {
            Curve *snapped = grids[j]->snapCurve(c);
            std::vector<string> curveData = snapped->concatData(len);
            qsk->addPoint(c->getId(),curveData);
            delete snapped ;
        }
    }

}
std::pair<int,Curve *> CurveGridMainUtils::nn(Curve *q){
    std::string id = q->getId();
    for (size_t i = 0; i < qsk->size(); i++) {
        // We find the matching vector in our database
        if (id == qsk->operator[](i)->itemId) {
            // We get the nn on the vector space
            #ifdef HASH_TABLE
            auto x = ht->search_query_neighbour(qsk->operator[](i),params.L * 10);
            #endif
            #ifdef HYPERCUBE
            auto x = ht->nn(qsk->operator[](i));
            #endif
            if (x.second == NULL) {
                std::cout << "No nearest neighbour" << '\n';
                continue ;
            }
            // we match the found vector to its parent in the curve space
            for (size_t j = 0; j < db->getSize(); j++) {
                if (x.second->itemId == db->getCurve(j)->getId()) {
                    std::pair<int,Curve *> r (x.first,db->getCurve(j));
                    return r ;
                }
            }
            break ;
        }
    }
}

std::pair<int,Curve *> CurveGridMainUtils::linear_search(Curve *q) {
    Curve *b ;
    int min = INFTY ;
    for (size_t i = 0; i < db->getSize(); i++) {
        int dist = db->getCurve(i)->dtwDistance(q);
        if (dist < min) {
            b = db->getCurve(i) ;
            min = dist ;
        }
    }
    std::pair<int,Curve *> ret (min,b);
    return ret ;
}

void CurveGridMainUtils::runQueries(void) {
    ofstream outfile ;
    outfile.open(params.output_file);
    for (size_t i = 0; i < qs->getSize(); i++) {
        Curve *q = qs->getCurve(i);

        clock_t begin1 = clock();
        auto tLsh = nn(q);
        clock_t end1 = clock();
        double elapsed_secs_nn = double(end1 - begin1) / CLOCKS_PER_SEC;

        clock_t begin2 = clock();
        auto tTrue = linear_search(q);
        clock_t end2 = clock();
        double elapsed_secs_ls = double(end2 - begin2) / CLOCKS_PER_SEC;
        if (tLsh.second == NULL) {
            continue ;
        }

        outfile << "Query: " << q->getId() << std::endl ;
        outfile << "Nearest neighbor: " << tLsh.second->getId() << std::endl ;
        outfile << "distanceLSH: " << tLsh.first << std::endl ;
        outfile << "distanceTrue: " << tTrue.first << std::endl ;
        outfile << "tLSH: " << elapsed_secs_nn << std::endl ;
        outfile << "tTrue: " << elapsed_secs_ls << std::endl ;

        std::cout << "Point " << q->getId() << " " << " lsh nn = " << tLsh.second->getId() << " with distance << " << tLsh.first << " computed in " << elapsed_secs_nn << " s " << " true nn = " << tTrue.second->getId() << " with distance " << tTrue.first << " computed in " << elapsed_secs_ls << " s" << std::endl ;
        if (tTrue.first > 0) {
            double AF  = ((double) tLsh.first) / ((double) tTrue.first) ;
            if (AF > maxAF) {
                maxAF = AF ;
            }
            sumAF += AF ;
        }
        if (tTrue.second->getId() == tLsh.second->getId()) {
            hits++;
        } else {
            misses++ ;
            errorsum += abs(tLsh.first - tTrue.first); // calculate the error
        }

    }
    cout << "hits=" << hits << " misses=" << misses << " maxAF=" << maxAF << " averageAF= " << sumAF / qs->getSize() << std::endl ;
    outfile.close();
}

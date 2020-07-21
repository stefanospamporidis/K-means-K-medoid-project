//
//  CubeUtils.cpp
//  project1
//
//  Created by <author> on 08/10/2019.
//
//

#include "CubeUtils.hpp"

CubeUtils::CubeUtils()  {
    db = new Database();
    qs = new Database();
    errorsum = 0 ;
    hits = 0 ;
    misses = 0 ;
    maxAF = -1 ;
    sumAF = 0 ;
}
CubeUtils::~CubeUtils() {
    //db->print();
    //qs->print();
    delete db ;
    delete qs ;
    delete cube ;

}

void CubeUtils::getArgs(int argc,char **argv) {
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
            {"k"    , required_argument , 0 , 'k'},
            {"M"           , required_argument , 0 , 'M'},
            {"--probes"           , required_argument , 0 , 'p'},
            {"o"          , required_argument , 0 , 'o'},
            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "d:q:k::M::p::o:",
        long_options, &option_index);

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
                if (optarg) {
                    params.K = atoi(optarg);
                }else
                    params.K = 3 ;
                break;
            case 'M':
                if (optarg) {
                    params.M = atoi(optarg);
                }else
                    params.M = 10 ;
                break;
            case 'p':
                if (optarg) {
                    params.probes = atoi(optarg);
                }else
                    params.probes = 2 ;
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
void CubeUtils::printArgs(void) {
    cout << "Input File " << params.input_file << endl ;
    cout << "Query File " << params.query_file << endl ;
    cout << "K " << params.K << endl ;
    cout << "M " << params.M << endl ;
    cout << "Probes " << params.probes << endl ;
    cout << "Output File " << params.output_file << endl ;

}
// Used code from https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
void CubeUtils::getPoints(){
    std::ifstream file(params.input_file);
    //std::istringstream str(file);

    while (!file.eof()) {
        std::vector<std::string>    m_data;

        std::string         line;
        std::getline(file, line);

        std::stringstream   lineStream(line);
        std::string         cell;

        m_data.clear();
        while(std::getline(lineStream, cell, ' '))
        {
            m_data.push_back(cell);
        }
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
        string id = m_data[0] ;
        m_data.erase(m_data.begin());
        if (m_data[m_data.size() - 1].compare("\r") == 0) {
            m_data.pop_back() ;
            //std::cout << "is r" << std::endl ;
        }
        //m_data.pop_back();
        db->addPoint(id,m_data);

        //std::cout << std::endl ;
    }

}
void CubeUtils::initHypercube(void) {
    cube = new Hypercube(db,params.K,params.probes,params.M);

}

void CubeUtils::parseQueries(void) {
    std::ifstream file(params.query_file);
    //std::istringstream str(file);

    while (!file.eof()) {
        std::vector<std::string>    m_data;

        std::string         line;
        std::getline(file, line);

        std::stringstream   lineStream(line);
        std::string         cell;

        m_data.clear();
        while(std::getline(lineStream, cell, ' '))
        {
            m_data.push_back(cell);
        }
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
        string id = m_data[0] ;
        m_data.erase(m_data.begin());
        if (m_data[m_data.size() - 1].compare("\r") == 0) {
            m_data.pop_back() ;
            //std::cout << "is r" << std::endl ;
        }
        //m_data.pop_back();
        //std::cout << "Line with id = " << id << std::endl ;
        qs->addPoint(id,m_data);

        //std::cout << std::endl ;
    }

}
std::pair<int,Point *> CubeUtils::nn(Point *q){
}
std::pair<int,Point *> CubeUtils::linear_search(Point *q) {
    Point *b ;
    int min = INFTY ;
    for (size_t i = 0; i < db->size(); i++) {
        int dist = Hash::Manhattan_Distance(db->operator[](i),q);
        if (dist < min) {
            b = db->operator[](i) ;
            min = dist ;
        }
    }
    std::pair<int,Point *> ret (min,b);
    return ret ;
}
void CubeUtils::runQueries(void) {
    ofstream outfile ;
    outfile.open(params.output_file);
    for (size_t i = 0; i < qs->size(); i++) {
        Point *q = qs->operator[](i);

        clock_t begin1 = clock();
        auto tLsh = cube->nn(q);
        clock_t end1 = clock();
        double elapsed_secs_nn = double(end1 - begin1) / CLOCKS_PER_SEC;

        clock_t begin2 = clock();
        auto tTrue = linear_search(q);
        clock_t end2 = clock();
        double elapsed_secs_ls = double(end2 - begin2) / CLOCKS_PER_SEC;

        outfile << "Query: " << q->itemId << std::endl ;
        outfile << "Nearest neighbor: " << tLsh.second->itemId << std::endl ;
        outfile << "distanceLSH: " << tLsh.first << std::endl ;
        outfile << "distanceTrue: " << tTrue.first << std::endl ;
        outfile << "tLSH: " << elapsed_secs_nn << std::endl ;
        outfile << "tTrue: " << elapsed_secs_ls << std::endl ;

        std::cout << "Point " << q->itemId << " " << " lsh nn = " << tLsh.second->itemId << " with distance << " << tLsh.first << " computed in " << elapsed_secs_nn << " s " << " true nn = " << tTrue.second->itemId << " with distance " << tTrue.first << " computed in " << elapsed_secs_ls << " s" << std::endl ;
        double AF  = ((double) tLsh.first) / ((double) tTrue.first) ;
        if (AF > maxAF) {
            maxAF = AF ;
        }
        sumAF += AF ;
        if (tTrue.second->itemId == tLsh.second->itemId) {
            hits++;
        } else {
            misses++ ;
            errorsum += abs(tLsh.first - tTrue.first); // calculate the error
        }

    }
    cout << "hits=" << hits << " misses=" << misses << " maxAF=" << maxAF << " averageAF= " << sumAF / qs->size() << std::endl ;
    outfile.close();
}

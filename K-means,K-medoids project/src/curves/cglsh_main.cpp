#include "cglsh_main.h"
int main(int argc, char **argv) {
    CurveGridMainUtils utils ;
    srand(time(NULL));


    if (argc < 5) {
        std::cerr << "example usage : \n ./curve_grid_lsh -d <input file> -q <query file> --k_vec <int> --L_grid <int> -o <output file>" << '\n';
        return -1 ;
    }
    utils.getArgs(argc,argv);
    utils.printArgs();
    utils.getPoints();
    utils.initGrids();
    utils.initHTS();
    utils.parseQueries();
    utils.runQueries();

    return 0;
}

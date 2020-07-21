#include "main.h"
#include "CubeUtils.hpp"
int main(int argc, char **argv){
	CubeUtils utils ;
	srand(time(NULL));


	if (argc < 5) {
		std::cerr << "example usage : \n ./cube -d <input file> -q <query file> -k <int> -M <int> --probes <int> -o <output file>" << '\n';
		return -1 ;
	}
	utils.getArgs(argc,argv);
	utils.printArgs();
	utils.getPoints();
	utils.initHypercube();
	utils.parseQueries();
	utils.runQueries();

	return 0 ;

}

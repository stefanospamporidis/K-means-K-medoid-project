#include "main.h"

int main(int argc, char **argv){
	MainUtils utils ;
	srand(time(NULL));


	if (argc < 5) {
		std::cerr << "example usage : \n ./lsh -d <input file> -q <query file> -k <int> -L <int> -o <output file>" << '\n';
		return -1 ;
	}
	utils.getArgs(argc,argv);
	utils.printArgs();
	utils.getPoints();
	utils.initHTS();
	utils.parseQueries();
	utils.runQueries();
	/*Point* p = new Point;
	p->itemId="i1";
	p->array.push_back(1.3);
	p->array.push_back(2.5);
	db.addPoint(p);*/

	//cout<<db.database.size()<<endl;
	//cout<<db.database[15]->array.at(8)<<endl;
	//db.cleanUp();
	//cout<<db.database.size()<<endl;

	return 0 ;

}

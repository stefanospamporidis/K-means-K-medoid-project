#include "Hashtable.h"



Hash::Hash(int k,float rad,int size,int d , Database *dbS)  // Constructor
{
    db = dbS ;
    this->k=k;
    radius=rad;
    hsize=size;
    w= W_CONST;
    this->d=d;
    for (int i=0;i<size;i++){
    	htable.push_back(new vector<Point *>);
    }
    m = ((uint64_t) pow(2,32)) -  5;

   	create_Starting_Points();
}
/*
void Hash::create_Starting_Points(){
	int number=k*3;
	vector <Point *> sp; //o pinakas twn starting points
	Point *spp; //proswrinos pointer gia ta starting points
	int i,j,intw=w;

	for (i=0;i<number;i++){
		spp=new Point;
		spp->itemId="N";

		for (j=0;j<d;j++){
            float floatPart = ((float)rand()/RAND_MAX) ;
            float intPart = uniform_distribution(0,intw-1);
			spp->array.push_back(intPart + floatPart); //((float)rand()/RAND_MAX) dinei enan pragmatiko ari8mo apo to 0 ws to 1
		} //ton opoio pros8etw me ena akeraio ari8mo apo to 0 ws to w-1 gia na para3w enan ari8mo apo to 0 ws to w.
		sp.push_back(spp);
	}
	for (i=0;i<k;i++){
		int position=rand()%number; //einai o ari8mos pou sumvolizei mia apo tis "grammes" tou pinaka sp o opoios exei k*3 random starting points
		start_points.push_back(sp[position]);
		sp[position]->itemId="O"; //markarw ta simeia pou 8a kratisw gia ti g etsi wste na diagra4w ta upoloipa
	}
	for (i=0;i<sp.size();i++){ //diagrafw ta simeia pou de 8a xrisimopoiisw gia tin h
		if (sp[i]->itemId=="N"){
			delete sp[i];
		}
	}
}
*/
// Different implementation of starting points
void Hash::create_Starting_Points(void) { //dimiourgia starting points
    for (size_t i = 0; i < k; i++) { //ta starting points einai ta simeia twn opoiwn tis diastaseis tou si xrisimopoioume gia 
        Point *sp = new Point() ; //ton upologismo tou a
        for (size_t j = 0; j < d; j++) {
            float floatPart = ((float)rand()/RAND_MAX) ;
            float intPart = uniform_distribution(0,w-1);
            sp->array.push_back(intPart + floatPart);
        }
        start_points.push_back(sp);
    }


}
void Hash::insert_Database(void){ //kanoume to hashing mesw tis g kai analoga me to ti epistefei ta vazoume sto antistoixo bucket
	for (int i=0;i<db->size();i++){
        Point *x = db->operator[](i);
		int bucket_number=g(x);
		htable[bucket_number]->push_back(x);
	}
}
/*
int Hash::h(Point *x,Point *s){
	int i,j;
	Point a;
	for (i=0;i<s->array.size();i++){ //3ekinaw apo to 2o stoixeio giati to prwto einai to item tou Point
		int temp= abs(floor(((double) (x->array[i])- (s->array[i]) )/w)); // sumvolizei tin pra3i ai=(xi-si)/w pou vrisketai stis diafaneies gia na paragoume tis diastaseis tou a
		a.array.push_back(temp);
	}
	int m=getmax(a)+1;
    //long m = pow(2,32) - 5 ;
    unsigned int sum=0;
	for (i=a.array.size()-1,j=0;i>=0;i--,j++){
		sum+=(mod_Calculator(m,j,256,a.array[i]) % 256); //kanei ti pra3i (ai+m*ai+...+m^(n-1)*ai)%M
	}
	return sum % 256; //to M sumfwna me tis diafaneies einai 2^(32/k) opou k=4 ara 2^8=256
}
*/

unsigned int Hash::h(Point *x,Point *s){ //ulopoiisi twn h(k) pou xrisimopoiountai apo tin g 
    vector<int> a ;
    //std::vector<unsigned int>  sumTerms ;
    unsigned int sum = 0 ;
    for (int i = 0; i < d; i++) {
        int temp = floor ( ((double ) x->array[i] - s->array[i]) / w );
        a.push_back(temp );
    }
    for (int i = 0; i < d; i++) {
        sum += calculate_mod(m,i,256,a[a.size() - i - 1]) ;

    }
    /*
    for (int i = 0; i < sumTerms.size(); i++) {
        sum += sumTerms[i] ;
    }
    */
    return sum % 256 ;
}
unsigned int Hash::calculate_mod(unsigned int m,int power,unsigned int M,int a) { //kanei ti pra3i (ai+m*ai+...+m^(n-1)*ai)%M
    if (a == 0) {
        return 0 ;
    }
    unsigned int c = 1 ;
    for (int i = 0; i < power; i++) {
        // c = (c * m) % M ; ==
        c = ((c) * (m)) % M ;
    }
    unsigned int number = ((((unsigned int )a) ) * (c )) % M ;
    return number ;
}


unsigned int Hash::g(Point *x){ //i ulopoisi tis g 
	unsigned int sum=0;
	int i;
	for (i=0;i<k;i++){
        unsigned int r = h(x,start_points[i]) ;
        r = r << ((k - i - 1)*(32 / k)) ; // Move the result to the left
		sum += r ;
	}
	return ( sum) % ((unsigned int ) hsize);
}
void Hash::printBuckets(void) {
    for (size_t i = 0; i < htable.size(); i++) {
        std::cout << "Bucket " << i << ":" << htable[i]->size() << '\n';
    }
}
std::pair<int,Point *> Hash::search_query_neighbour(Point *q,int maxR){ //pairnei ena query apo to arxeio pou mas exoun dwsei,kanei to hashing kai vriskei to pio kontino .
    // To maxR antistoixei sto 3L stis diafaneies
	//simeio se auto me vasi ti manhattan distance
	int i;
	int bucket_number=g(q);
    // Se periptosi pou einai adeio to htable . Allios yperxe error me outofbounds
    if (htable[bucket_number]->size() == 0) {
        cout << "Empty bucket" << std::endl ;
        std::pair<int,Point *> ret(INFTY,NULL) ;
        return ret ;
    }
	int min_distance=Manhattan_Distance(q,htable[bucket_number]->at(0)); //krataei ti minimum distance,vazw ws default timi tin apostasi apo to
	//prwto simeio tou bucket
	int distance; //krataei ti manhattan distance twn simeiwn kai an einai mikroteri tis min distance 8a tin antika8istw
	Point * neighbour=htable[bucket_number]->at(0); //krataei ton pio kontino geitona,vazw ws default timi to stringId tou prwtou stoixeiou
	for (i=0;i<htable[bucket_number]->size();i++){ //htable[bucket_number].size() einai to mege8os tou bucket pou mpike to query,pou ousiastika
		//einai to pli8os twn simeiwn tis geitonias
		distance=Manhattan_Distance(q,htable[bucket_number]->at(i));
		if (distance<min_distance){
			min_distance=distance;
			neighbour=htable[bucket_number]->at(i);
		}
        if (i > maxR) {
            break ;
        }
	}
    std::pair<int,Point *> ret(min_distance,neighbour);
    return ret ;
}

int Hash::getmax(Point & a){ //pairnw apo to simeio a ti megaluteri diastasi
	int max=a.array[0];
	for (int i=1;i<a.array.size();i++){
		if (max<a.array[i]){
			max=a.array[i];
		}
	}
	return max;
}

unsigned int Hash::mod_Calculator(unsigned int m,unsigned int power,unsigned int M,int ai){  //to xrisimopoiw gia na upologisw to upoloipw twn dunamewn tou m pou xrisimopoiountai stin h(x)
	unsigned int i;
	unsigned int numberm=1;
	unsigned int numbera=1;
	unsigned int number=1;
	for (i=0;i<power;i++){
		numberm = (numberm  * m ) % M ;
	}
	numberm=numberm%M; //dunami tou m mod M
	numbera=ai%M; //a mod M
	number=(numberm*numbera); //(m * a) mod M
    
	return number;
}
//https://stackoverflow.com/questions/11641629/generating-a-uniform-distribution-of-integers-/in-c
int Hash::uniform_distribution(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX);
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}


int Hash::Manhattan_Distance(Point * q,Point * x){
	int manhattan_distance = 0;
	for (int i=0;i<q->array.size();i++){
        manhattan_distance += abs(q->array[i] - x->array[i]);
        /*
		if (q->array[i]>x->array[i]){ //an i diastasi tou q einai megaluteri apo tou x tote afairw to x apo to q wste na parw 8etiko ari8mo
			manhattan_distance+=q->array[i]-x->array[i];
		}
		if (x->array[i]>q->array[i]){ //antistoixa sti periptwsi opou i diastasi tou x na einai megaluteri apo to q
			manhattan_distance+=x->array[i]-q->array[i];
		}
        */
	}
	return manhattan_distance;
}

Hash::~Hash(){ //destructor tou hashtable
	for (int i=0;i<hsize;i++){
		delete htable[i];
	}
    for (size_t i = 0; i < start_points.size(); i++) {
        delete start_points[i];
    }
}

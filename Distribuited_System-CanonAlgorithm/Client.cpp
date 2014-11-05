#include <Ice/Ice.h>
#include "Canon.h"

using namespace Ice;
using namespace Canon;

class Client: public Ice::Application {
	
	Canon::DoubleMatrix getRandomMatrix(int order){
		srand((unsigned)time(NULL));
		Canon::DoubleMatrix result;
		double value;
		
		for(int i=0; i<order; i++){
			Canon::DoubleArray array;
			for (int j = 0; j < order; j += 1){
				value=((double)rand()/(double)RAND_MAX);
				array.push_back(value);
			}
			result.push_back(array);
		}
		

		return result;
	}
	
  int run(int argc, char* argv[]) {
    ObjectPrx proxy = communicator()->stringToProxy(argv[1]);
    CollectorPrx collector = CollectorPrx::checkedCast(proxy);
    
    ObjectPrx proxy2 = communicator()->stringToProxy(argv[2]);
    ProcessorPrx processor = ProcessorPrx::checkedCast(proxy2);
    

    
    Canon::DoubleMatrix matrix = getRandomMatrix(3);
    
    Matrix newMatrix{  5, matrix, "matrix1" };
    
    
	Canon::DoubleMatrix matrix2 = getRandomMatrix(3);
	
	Matrix newMatrix2{  5, matrix2, "matrix2" };

    //collector->inject(2,matrix);
    collector->chekedTest(newMatrix,newMatrix2);
    processor->init(0,0,processor,processor,collector);
	processor->injectA(newMatrix, 0);
	processor->injectB(newMatrix2, 0);
	//std::cout << "Es valida:" <<  << std::endl;

	
    return 0;
  }
};

int main(int argc, char* argv[]) {
  Client app;
  return app.main(argc, argv);
}

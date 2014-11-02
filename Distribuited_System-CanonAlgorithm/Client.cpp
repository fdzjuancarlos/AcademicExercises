#include <Ice/Ice.h>
#include "Canon.h"

using namespace Ice;
using namespace Canon;

class Client: public Ice::Application {
  int run(int argc, char* argv[]) {
    ObjectPrx proxy = communicator()->stringToProxy(argv[1]);
    CollectorPrx collector = CollectorPrx::checkedCast(proxy);
    
    ObjectPrx proxy2 = communicator()->stringToProxy(argv[2]);
    ProcessorPrx processor = ProcessorPrx::checkedCast(proxy2);
    

    
    Canon::DoubleArray array1;
    array1.push_back(1.0);
    array1.push_back(5.3);
    Canon::DoubleArray array2;
    array2.push_back(2.3);
    array2.push_back(7.2);
    Canon::DoubleMatrix matrix;
    matrix.push_back(array1);
    matrix.push_back(array2);
    
    Matrix newMatrix{  5, matrix, "matrix1" };

    //collector->inject(2,matrix);
    collector->chekedTest(newMatrix,newMatrix);
    processor->init(0,0,processor,processor,collector);
	processor->injectA(newMatrix, 0);
	processor->injectB(newMatrix, 0);
	//std::cout << "Es valida:" <<  << std::endl;

	
    return 0;
  }
};

int main(int argc, char* argv[]) {
  Client app;
  return app.main(argc, argv);
}

#include <Ice/Ice.h>
#include "Collector.h"

using namespace Ice;
using namespace Canon;

class Client: public Ice::Application {
  int run(int argc, char* argv[]) {
    ObjectPrx proxy = communicator()->stringToProxy(argv[1]);
    CollectorPrx collector = CollectorPrx::checkedCast(proxy);
    
    Canon::FloatArray array1;
    array1.push_back(1.0);
    array1.push_back(5.3);
    Canon::FloatArray array2;
    array2.push_back(2.3);
    array2.push_back(7.2);
    Canon::FloatMatrix matrix;
    matrix.push_back(array1);
    matrix.push_back(array2);

    collector->inject(2,matrix);

    return 0;
  }
};

int main(int argc, char* argv[]) {
  Client app;
  return app.main(argc, argv);
}

#include <Ice/Ice.h>
#include "CollectorI.h"

using namespace std;
using namespace Ice;

class Server: public Application {
  int run(int argc, char* argv[]) {
    Canon::CollectorPtr servant = new Canon::CollectorI();
    Canon::ProcessorPtr processor1 = new Canon::ProcessorI();

    ObjectAdapterPtr adapter =
         communicator()->createObjectAdapter("CollectorAdapter");
    ObjectPrx proxy = adapter->add(
	 servant, communicator()->stringToIdentity("collector1"));

	ObjectAdapterPtr adapter1 =
         communicator()->createObjectAdapter("ProcessorAdapter");
    ObjectPrx proxy1 = adapter1->add(
	 processor1, communicator()->stringToIdentity("processor1"));

	

    cout << communicator()->proxyToString(proxy) << endl;
    cout << communicator()->proxyToString(proxy1) << endl;
	    
    adapter->activate();
    std::cout << "not blocked" << std::endl;
    adapter1->activate();

    shutdownOnInterrupt();
    communicator()->waitForShutdown();

    return 0;
  }
};

int main(int argc, char* argv[]) {
  Server app;
  return app.main(argc, argv);
}

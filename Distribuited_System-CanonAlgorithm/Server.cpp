#include <Ice/Ice.h>
#include "CollectorI.h"

using namespace std;
using namespace Ice;

class Server: public Application {
  int run(int argc, char* argv[]) {
    Canon::CollectorPtr servant = new Canon::CollectorI();
    //Example::PrinterPtr servant2 = new Example::PrinterI();

    ObjectAdapterPtr adapter =
         communicator()->createObjectAdapter("CollectorAdapter");
    ObjectPrx proxy = adapter->add(
	 servant, communicator()->stringToIdentity("collector1"));

    //cout << communicator()->proxyToString(proxy) << endl;


	

    cout << communicator()->proxyToString(proxy) << endl;
	    
    adapter->activate();

    shutdownOnInterrupt();
    communicator()->waitForShutdown();

    return 0;
  }
};

int main(int argc, char* argv[]) {
  Server app;
  return app.main(argc, argv);
}

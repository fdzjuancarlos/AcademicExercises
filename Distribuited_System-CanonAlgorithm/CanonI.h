#ifndef __CanonI_h__
#define __CanonI_h__

#include <Canon.h>

namespace Canon
{

class CollectorI : virtual public Collector
{
public:

    virtual void inject(::Ice::Int,
                        const ::Canon::Matrix&,
                        const Ice::Current&);
};

class ProcessorI : virtual public Processor
{
	Matrix A;
public:

    virtual void init(::Ice::Int,
                      ::Ice::Int,
                      const ::Canon::ProcessorPrx&,
                      const ::Canon::ProcessorPrx&,
                      const ::Canon::CollectorPrx&,
                      const Ice::Current&);

    virtual void injectA(const ::Canon::Matrix&,
                         ::Ice::Int,
                         const Ice::Current&);

    virtual void injectB(const ::Canon::Matrix&,
                         ::Ice::Int,
                         const Ice::Current&);
};

class FrontendI : virtual public Frontend
{
public:

    virtual ::Canon::Matrix multiply(const ::Canon::Matrix&,
                                     const ::Canon::Matrix&,
                                     const Ice::Current&);
};

}

#endif

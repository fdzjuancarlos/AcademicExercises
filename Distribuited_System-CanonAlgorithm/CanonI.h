#ifndef __CanonI_h__
#define __CanonI_h__

#include <Canon.h>

namespace Canon
{

class CollectorI : virtual public Collector
{
	const Matrix* A;
	const Matrix* B;
public:

    virtual void inject(::Ice::Int,
                        const ::Canon::Matrix&,
                        const Ice::Current&);

    virtual bool chekedTest(const ::Canon::Matrix&,
                            const ::Canon::Matrix&,
                            const Ice::Current&);
};

class ProcessorI : virtual public Processor
{
	const Matrix* A;
	const Matrix* B;
	::Canon::ProcessorPrx _above;
    ::Canon::ProcessorPrx _left;
    Canon::CollectorPrx _target;
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

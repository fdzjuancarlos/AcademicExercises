#ifndef __CollectorI_h__
#define __CollectorI_h__

#include <Collector.h>

namespace Canon
{

class CollectorI : virtual public Collector
{
public:

    virtual void inject(::Ice::Int,
                        const ::Canon::FloatMatrix&,
                        const Ice::Current&);
};

class ProcessorI : virtual public Processor
{
	::Canon::FloatMatrix A;
public:

    virtual void init(::Ice::Int,
                      ::Ice::Int,
                      const ::Canon::ProcessorPrx&,
                      const ::Canon::ProcessorPrx&,
                      const ::Canon::CollectorPrx&,
                      const Ice::Current&);

    virtual void injectA(const ::Canon::FloatMatrix&,
                         ::Ice::Int,
                         const Ice::Current&);

    virtual void injectB(const ::Canon::FloatMatrix&,
                         ::Ice::Int,
                         const Ice::Current&);
};

class classProcessorI : virtual public classProcessor,
                        virtual public ::Canon::ProcessorI
{
public:
};

}

#endif

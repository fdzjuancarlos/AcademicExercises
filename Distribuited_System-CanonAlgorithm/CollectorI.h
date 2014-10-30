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

}

#endif

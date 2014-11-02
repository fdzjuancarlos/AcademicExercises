
#include <CanonI.h>

void
Canon::CollectorI::inject(::Ice::Int index,
                          const ::Canon::Matrix& result,
                          const Ice::Current& current)
{
	for(float i=0; i < result.data.size(); i++){
		for(float j=0; j < result.data.size(); j++)
			std::cout << result.data.at(i).at(j) << " ";
			
		std::cout << std::endl;
	}
}

void
Canon::ProcessorI::init(::Ice::Int index,
                        ::Ice::Int order,
                        const ::Canon::ProcessorPrx& above,
                        const ::Canon::ProcessorPrx& left,
                        const ::Canon::CollectorPrx& target,
                        const Ice::Current& current)
{
	target->inject(0,A);
}

void
Canon::ProcessorI::injectA(const ::Canon::Matrix& a,
                           ::Ice::Int step,
                           const Ice::Current& current)
{
	std::cout << (&A==NULL) << (&A!=NULL);
	A = a;
}

void
Canon::ProcessorI::injectB(const ::Canon::Matrix& b,
                           ::Ice::Int step,
                           const Ice::Current& current)
{
}

::Canon::Matrix
Canon::FrontendI::multiply(const ::Canon::Matrix& a,
                           const ::Canon::Matrix& b,
                           const Ice::Current& current)
{
    return ::Canon::Matrix();
}

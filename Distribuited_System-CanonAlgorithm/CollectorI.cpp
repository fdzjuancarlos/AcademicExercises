
#include <CollectorI.h>

void
Canon::CollectorI::inject(::Ice::Int index,
                          const ::Canon::FloatMatrix& matrix,
                          const Ice::Current& current)
{
	for(float i=0; i < matrix.size(); i++){
		for(float j=0; j < matrix.at(0).size(); j++)
			std::cout << matrix.at(i).at(j) << " ";
			
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
	target->inject(0, A);
}

void
Canon::ProcessorI::injectA(const ::Canon::FloatMatrix& a,
                           ::Ice::Int step,
                           const Ice::Current& current)
{
	A = a;
}

void
Canon::ProcessorI::injectB(const ::Canon::FloatMatrix& b,
                           ::Ice::Int step,
                           const Ice::Current& current)
{

}

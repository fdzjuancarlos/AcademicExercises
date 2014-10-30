
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

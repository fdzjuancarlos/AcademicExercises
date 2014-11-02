
#include <CanonI.h>

void multiplyMatrix(const ::Canon::Matrix *A, const ::Canon::Matrix *B, Canon::DoubleMatrix &product);

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
	_target = target;
}

void
Canon::ProcessorI::injectA(const ::Canon::Matrix& a,
                           ::Ice::Int step,
                           const Ice::Current& current)
{
	A = &a;
	if(B!=NULL){
    	Canon::DoubleMatrix product;
		
		multiplyMatrix(A,B,product);
		
		Matrix result{ product.size(), product, "P1"};
		
		_target->inject(product.size(), result);
		A=NULL;
		B=NULL;
	}
}

void
Canon::ProcessorI::injectB(const ::Canon::Matrix& b,
                           ::Ice::Int step,
                           const Ice::Current& current)
{
	B = &b;
	if(A!=NULL){
    	Canon::DoubleMatrix product;
		
		multiplyMatrix(A,B,product);
		
		Matrix result{ product.size(), product, "P1"};
		
		_target->inject(product.size(), result);
		A=NULL;
		B=NULL;
	}
}

::Canon::Matrix
Canon::FrontendI::multiply(const ::Canon::Matrix& a,
                           const ::Canon::Matrix& b,
                           const Ice::Current& current)
{
    return ::Canon::Matrix();
}


void multiplyMatrix(const ::Canon::Matrix *A, const ::Canon::Matrix *B, Canon::DoubleMatrix &product){
	int size = A->data.size();
	
	for(int i = 0; i<size ; i++){
		Canon::DoubleArray innerArray;
		for(int j=0; j<size; j++){
			innerArray.push_back(0);
		}
		product.push_back(innerArray);
	}
	
	for (int y = 0; y < size; y++) {
  		for (int x = 0; x < size; x++) {
			for (int inner = 0; inner < size; inner++) {
	  			product.at(y).at(x) += A->data.at(y).at(inner) * B->data.at(inner).at(x);
	 		}
		}
	}
}

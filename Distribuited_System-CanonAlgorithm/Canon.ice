module Canon{
	
	sequence<double> DoubleArray;
	sequence<DoubleArray> DoubleMatrix;
	
	struct Matrix { 
		int ncols;
		DoubleMatrix data; 
		string UUID;
	};
	
	interface Collector {
		void inject(int index, Matrix result); 
	};
	
	interface Processor {
		void init(int index , int order , Processor* above, Processor* left, Collector* target);
		void injectA(Matrix a, int step); 
		void injectB(Matrix b, int step);
	};
	
	interface Frontend {
		Matrix multiply(Matrix a, Matrix b); 
	};
};

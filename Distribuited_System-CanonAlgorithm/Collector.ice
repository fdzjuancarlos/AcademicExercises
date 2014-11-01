module Canon{
	
	sequence<float> FloatArray;
	sequence<FloatArray> FloatMatrix;
	
	/*struct Matrix { 
		int ncols;
		Ice::DoubleSeq data; 
		string UUID;
	};*/
	
	//FloatMatrix A;
	
	interface Collector {
		void inject(int index, FloatMatrix matrix); 
	};
	
	interface Processor {
		void init(int index , int order , Processor* above, Processor* left, Collector* target);
		void injectA(FloatMatrix a, int step); 
		void injectB(FloatMatrix b, int step);
	};
	
	class classProcessor implements Processor{
		FloatMatrix A;
	};
};

module Canon{
	
	sequence<float> FloatArray;
	sequence<FloatArray> FloatMatrix;
	
	interface Collector {
		void inject(int index, FloatMatrix matrix); 
	};
};

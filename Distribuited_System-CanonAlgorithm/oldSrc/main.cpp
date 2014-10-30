
#include<iostream>
#include <vector>

using namespace std;

void printArray(vector<vector<float> > *array){
	
	for(float i=0; i < array->size(); i++){
		for(float j=0; j < array->at(0).size(); j++)
			cout << array->at(i).at(j) << " ";
			
		cout << endl;
	}

}

vector<vector<float> >* multArray(vector<vector<float> > &array1, vector<vector<float> > &array2){
	
	vector<vector<float > >* product = new vector<vector<float > >;
	int size = array1.size();
	std::cout << array1.size() << std::endl;
	
	for(int i = 0; i<size ; i++){
		vector<float> innerArray;
		for(int j=0; j<size; j++){
			innerArray.push_back(0);
		}
		product->push_back(innerArray);
	}
	
	for (int y = 0; y < size; y++) {
  		for (int x = 0; x < size; x++) {
    		for (int inner = 0; inner < size; inner++) {
    			//std::cout << y << " " << x << " " << inner << std::endl;
      			product->at(y).at(x) += array1.at(y).at(inner) * array2.at(inner).at(x);
     		}
    		//std::cout << product->at(y).at(x) << "  ";
		}
//        std::cout << "\n";
    }
    
    return product;
	
}

int main(int argc, char *argv[]){
	
	vector<vector<float> > my_array; /* 2D Array */
	vector<float> otherArray;
	vector<float> otherArray2;
	otherArray.push_back(133);
	otherArray.push_back(12);
	otherArray2.push_back(7);
	otherArray2.push_back(15.3);
	
	my_array.push_back(otherArray);
	my_array.push_back(otherArray2);
	
	printArray(&my_array);
	vector<vector<float > > *result = multArray(my_array, my_array);
	printArray(result);
	
	return 0;
}


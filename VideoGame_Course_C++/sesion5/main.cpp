#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(const string &s, char delim);
vector<string> &split(const string &s, char delim, vector<string> &elems);
bool palindromo(const string &s);

int main(int argc, char *argv[]){
	
	string fileName("./");
	

	fileName += argv[1];
	ifstream file(fileName.c_str());
	
	cout << "Opening " << fileName << "..." << endl;
	
	if (!file.is_open()){
		cout << "Error, "<< fileName << "no existe" << endl;
		return -1;
	}
	
//	ostream infoFile("./infoFile.txt");
	
	string line;
	vector<string> words;
	int newLine=0, size=0, palindromos = 0;

	while (getline(file, line)){
		
		newLine++;
		size += line.size();
		words = split(line, ' ');
		
		for (unsigned i=0; i<words.size(); i++){
    		if(palindromo(words.at(i)))
    			palindromos++;
    	}
	}
	file.close();
	ofstream infoFile;
  	infoFile.open ("infoFile.txt");
 	infoFile << "Nombre: " << argv[1] << "\n";
 	infoFile << "Tamanyo: " << size << "\n";
 	infoFile << "Lineas: " << newLine << "\n";
 	infoFile << "Palabras Palindromo: " << palindromos << "\n";
  	infoFile.close();

	return 0;
}

bool palindromo(const string &s){
	bool esPalindromo = true;
	for(unsigned int i=0; i < s.size()/2; i++){
		if(s.at(i) != s.at(s.size()-i-1))
			esPalindromo=false;
	}
	
	return esPalindromo;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

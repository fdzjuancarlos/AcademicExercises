
#include<iostream>
using namespace std;

double getAverage(int arr[], int size)
{
  int    i, sum = 0;       
  double avg;          

  for (i = 0; i < size; ++i)
  {
    sum += arr[i];
   }

  avg = double(sum) / size;

  return avg;
}

int main(int size, char** heh){
	
	
	return 0;
}

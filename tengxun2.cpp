#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


int main(int argc, char const *argv[])
{
	int n;
    while (cin>>n){
       
      vector<int> vect;
      int i;
      int a;
      for (i = 0;i < n;i++){
      	cin>>a;
      	vect.push_back(a);
      }
      if (n == 1){
      	cout<<0<<" "<<0<<endl;
      	continue;
      }
     sort(vect.begin(),vect.end());
     int min_count,max_count,max_logarithm,min_logarithm;
     max_count = count(vect.begin(),vect.end(),vect[n-1]);
     min_count = count(vect.begin(),vect.end(),vect[0]);
     if (vect[0] == vect[n-1]){
        max_logarithm = (n*(n-1))/2;
        cout<<max_logarithm<<" "<<max_logarithm<<endl;
        continue;
     }else{
     	max_logarithm = max_count*min_count;
     }
     min_logarithm = 0;
     int min_value;
     int j;
     min_value = vect[1] - vect[0];
     for (i = 1;i < n;i++){
        if (vect[i] - vect[i-1] < min_value){
        	min_value = vect[i] - vect[i-1];
        }
     }

     for (i = n-1;i >= 0;i--){
     	for (j = i-1;j >= 0;j--){
     		if (vect[i] - vect[j] == min_value){
     			min_logarithm++;
     		}else
     		break;
     	}
     }
     cout<<min_logarithm<<" "<<max_logarithm<<endl;
    }
	return 0;
}
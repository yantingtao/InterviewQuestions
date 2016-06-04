/*==================================================================================
作者:颜廷涛
时间:2016/6/3
内容:3、有趣的数字
 
小Q今天在上厕所时想到了这个问题：有n个数，两两组成二元组，差最小的有多少对呢？差最大呢？
 
输入描述:
 
输入包含多组测试数据。
 对于每组测试数据：
N - 本组测试数据有n个数
a1,a2...an - 需要计算的数据
 保证:
1<=N<=100000,0<=ai<=INT_MAX.
 
输出描述:
 
对于每组数据，输出两个数，第一个数表示差最小的对数，第二个数表示差最大的对数。
 
输入例子:
 
6
 
45 12 45 32 5 6
 
输出例子:
 
1 2

======================================================================================*/
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
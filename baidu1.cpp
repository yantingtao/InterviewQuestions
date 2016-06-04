/*========================================================
作者:颜廷涛
时间:2016/6/4
内容:拉姆刚开始学习英文单词，对单词排序很感兴趣。
如果给拉姆一组单词，他能够迅速确定是否可以将这些单词排列在一个列表中，
使得该列表中任何单词的首字母与前一单词的尾字母相同。
你能编写一个程序来帮助拉姆进行判断吗？

输入描述:

  输入包含多组测试数据。

  对于每组测试数据，第一行为一个正整数n，代表有n个单词。

  然后有n个字符串，代表n个单词。

  保证：

  2<=n<=200,每个单词长度大于1且小于等于10,且所有单词都是由小写字母组成。

  


输出描述:
对于每组数据，输出"Yes"或"No"

输入例子:
  3
  abc
  cdefg
  ghijkl
  4
  abc
  cdef
  fghijk
  xyz
  

输出例子:
  Yes
  No
  
=========================================================*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
  using namespace std;
  int main(int argc, char const *argv[])
  {
  	int n;
  	while (cin>>n){
        if (n == 1 || n > 200){
        	continue;
        }
        vector<string> vect;
  		int i;
  		string tmp;
  		for (i = 0;i < n;i++){
         cin>>tmp;
            if (tmp.length() > 1 && tmp.length() <= 10)
              vect.push_back(tmp);
            else
                continue;
  		}
       sort(vect.begin(),vect.end());
       for (i = 0;i < n-1;i++){
       	if (vect[i][vect[i].length()-1] != vect[i+1][0]){
         cout<<"No"<<endl;
         continue;
       	}
       }
       cout<<"Yes"<<endl;
  	}
  	return 0;
  }
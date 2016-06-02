/*================================================================
作者:颜廷涛
时间:2016/6/2
内容:小Q最近遇到了一个难题：把一个字符串的大写字母放到字符串的后面，
各个字符的相对位置不变，且不能申请额外的空间。
你能帮帮小Q吗？
 
输入描述:
 
输入数据有多组，每组包含一个字符串s，且保证:1<=s.length<=1000.
 
输出描述:
 
对于每组数据，输出移位后的字符串。
 
输入例子:
 
AkleBiCeilD
 
输出例子:
 
kleieilABCD
=====================================================================*/
#include <string.h>
#include <ctype.h>
#include <iostream>
#define N 1000
using namespace std;
int main(int argc, char const *argv[])
{
	char pstr[N];
	memset(pstr,0,sizeof(pstr)); 
    gets(pstr);
    int len = strlen(pstr);
    int i,j;
    int k;
    for (i = len-1;i >= 0;i--){//从尾部开始
    	
    	if (islower(pstr[i])){//如果是小写字母就要往前移动寻找大写字母
           
           for (j = i-1;j >= 0;j--){//从前一位开始寻找大写字母
           	 
           	 if (isupper(pstr[j])){//找到了大写字母
               char tmp = pstr[j];//存储大写字母
               
               for (k = j;k < i;k++){//把小写字母和小字母到大写字母的往前移动一位
               	 pstr[k] = pstr[k+1];
               }
               pstr[i] = tmp;//大写字母代替之前的小写字母
               break;
           	 }
           }
    	}
    }
    cout<<pstr<<endl;
	return 0;
}
/*===========================================
*作者:颜廷涛
*时间:2016/5/31
*内容:处理海量大数据找出其中出现次数最多的
=============================================*/
#include <stdio.h>
#include <map>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <errno.h>
#include <string>
#define N 1000
using namespace std;

template<class T>
class list;

template<class T>
class hashtable;
//节点类
template<class T>
class  node
{
friend class list<T>;
friend class hashtable<T>;
template<class T1>
friend ostream& operator <<(ostream& out,node<T1>  tmp);

template<class T2>
friend ostream&  operator <<(ostream& out,list<T2> l1);
public:
	node(T _value){
      value=_value;
      next=NULL;
	}
	bool operator ==(node<T> *  tmp){
		return this->value==tmp->value;
	}
private:
	T value;
	node<T>* next;
};
template<class T>
ostream& operator <<(ostream& out,node<T>  tmp){
	 out<<tmp.value;
	 return out;
}

//链表类
template<class T>
class  list
{
template<class T1>
friend ostream&  operator <<(ostream& out,list<T1> l1);
public:
  /*========================================
  *函数名:list
  *函数参数: tmp head节点的初始值
  *函数作用:构造函数
  ===========================================*/
	list(node<T> * tmp=NULL){
		head=tmp;
		curr=NULL;
	}
	/*========================================
  *函数名:push_back
  *函数参数: newnode 插入节点
  *函数作用:在链表中插入值
  ===========================================*/
	void  push_back(node<T> * newnode){
        if(head==NULL)
        {
        	head=newnode;
        	curr=head;
        }
        else
        {
        	curr->next=newnode;
        	curr=newnode;
        }
        newnode=NULL;
	}
  /*========================================
  *函数名:list_delete
  *函数参数: value 删除的值
  *函数作用:删除在链表中所有值为value
  ===========================================*/
	void  list_delete(T value){
      node<T>* tmp = head;
      curr = head->next;
      if (head->value == value){
         head = curr;
         delete tmp;
         tmp = NULL;
      }
      else
      {
         while (curr != NULL){
            if (curr->value == value){ 
              tmp->next = curr->next;
              delete curr;
              curr = NULL;
            } 
            else
            {
               tmp = curr;
            }
            curr = curr->next;
         }
      }
	}
  /*========================================
  *函数名:list_exists
  *函数参数: tmp 查询的节点
  *函数作用:查询某个节点在list中是否存在
  ===========================================*/
	bool list_exists(node<T> *tmp){
	     bool isexists=false;
		  
      if(tmp==NULL){
		 	isexists=false;
		 }
		 if(tmp!=NULL){
            node<T>* t1=head;
            while(t1!=NULL){
            	if(t1->value==tmp->value){
            		isexists=true;
            		break;
            	}
            	t1=t1->next;
            }
		 }
		 return isexists;
	}

  /*========================================
  *函数名:getValue
  *函数参数: index 需要获取的值的位置
  *函数作用:获取对应位置的值
  ===========================================*/
   const  T  getValue(int index){
           int i = 0;
           string ptr = "-100";
           node<T>* tmp = NULL;
            tmp = head;
            while (i != index){
             
              if (tmp == NULL){
                 return ptr;
              }
              tmp = tmp->next;
              i++;
           }
             if (tmp != NULL){
              return tmp->value;
           }
           else
           {
             return ptr;
           }
        }

private:
   node<T> *head;
   node<T> *curr;
};
template<class T>
ostream&  operator <<(ostream& out,list<T> l1)
{
    node<T> * t=l1.head;
    while(t!=NULL)
    {
    	out<<*t<<'\t';
    	t=t->next;
    }
    return out;
}

//hash表类
template<class T>
class hashtable
{
public:
    typedef int (*hash)(T value);
  /*========================================
  *函数名:hashtable
  *函数参数: _fptr hash函数
  *函数作用:构造函数
  ===========================================*/  
	hashtable(hash _fptr)
	{
		int i;
		for(i=0;i<N;i++)
		{
			table[i]=NULL;
		}
		fptr=_fptr;
	}
  /*========================================
  *函数名:hash_insert
  *函数参数: value 插入的值
  *函数作用:在hash表中插入值
  ===========================================*/ 
	void  hash_insert(T value)
	{
      int key=fptr(value);  
      node<T> *newnode= new node<T>(value);
      if(table[key]==NULL)
      { 
          table[key]=newnode;        
      }  

     list[key].push_back(newnode);
     
	}
  /*========================================
  *函数名:hash_find
  *函数参数: value 查找的值
  *函数作用:在hash表中查找值
  ===========================================*/ 	
	bool hash_find(T value)
	{
	   bool isfind=false;
       int key=fptr(value);              
       if(table[key]==NULL)
       {
          isfind=false;
       }
       else
       {
       	 node<T> *tmp=new node<T>(value);
       	 isfind=list[key].list_exists(tmp);
       }
       return isfind;
	}

  /*========================================
  *函数名:hash_isempty
  *函数参数: i 查询的key在hashtable 中
  *函数作用:判断hash表中对应的key值是否空
  ===========================================*/  
 bool hash_isempty(int i)
 {
 	if (table[i] == NULL)
 		return true;
 	return false;
 }
  /*========================================
  *函数名:hash_lead_in
  *函数参数: filename[]是文件名 index key值
  *函数作用:把对应的key中链表导入文件中
  ===========================================*/  
void hash_lead_in(char filename[],int index)
{
 char buf[20] = {'\0'};
 int fd = open(filename,O_CREAT|O_EXCL|O_RDWR,0777);
    if (fd < 0){
     if (errno == EEXIST){
        fd = open(filename,O_RDWR);
        if (fd < 0){
          perror("open:");
          exit(-1);
        }
      }else{
        perror("open:");
        exit(-1);
      }
    }
    int len = 4096*256;
  write(fd," ",1);//制造空洞文件
  void* addr = mmap(NULL,len,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
  if (addr == NULL){
    perror("mmap:");
    exit(-1);
  }
  close(fd);
 int i = 0;
 while (strcmp(list[index].getValue(i).c_str(),"-100") != 0)
 {
    bzero(buf,sizeof(buf));
    strcpy(buf,list[index].getValue(i).c_str());
    memcpy(addr,buf,strlen(buf));
    addr = (char *)addr + strlen(buf);
    i++;
 }
   munmap(addr,len);
}
private:
	node<T> * table[N];
	hash fptr;
	list<T> list[N];
};

//外置hash函数
int hash_fun(string value)
{
    int sum=0;
    int i;
    for(i=0;i<value.length();i++)
    {
       sum+=value[i];
    }
    return sum%N;
}
  /*========================================
  *函数名:DownloadDataToHash
  *函数参数: filename[]是文件名 hash1 hash表
  *函数作用:把大文件中数据导入hash中
  ===========================================*/  
void DownloadDataToHash(char filename[],hashtable<string>& hash1)
{
    FILE* rfp;
    rfp = fopen(filename,"r+");
    if (rfp == NULL)
    {
    	perror("open:");
    	exit(-1);
    }
   
    char buf[1024];
    char *find;
     bzero(buf,sizeof(buf));
    while (fgets(buf,1024,rfp))
    {     
     hash1.hash_insert(buf);
     bzero(buf,sizeof(buf));
    }
    fclose(rfp);
}
  /*=======================================================
  *函数名:DealData
  *函数参数: pstr[]存放所有值的下标 hash1 hash表
  *函数作用:处理hash表中的每个key 值对应的链表并导入小文件中
  =========================================================*/ 
void DealData(int pstr[],hashtable<string>& hash1)
{
   int i;
   int index = 0;
   char filename[10] = {'\0'};
   i = 288;
   for (i = 0;i < N;i++)
   {
   	 if (!hash1.hash_isempty(i))
   	 {
   	 	  //记录下i方便后面读取查找
        pstr[index] = i;
        index++;
        sprintf(filename,"a%d.dat",i);
        hash1.hash_lead_in(filename,i);
   	 }
   }   
}

  /*=======================================================
  *函数名:findMaxCount
  *函数参数: filename文件名 savestring 保存出现次数最多的数据
  *函数作用:处理每个小文件找出出现次数最多的数据
  =========================================================*/ 
int findMaxCount(char filename[],char savestring[])
{
    FILE* rfp;
    rfp = fopen(filename,"r+");
    if (rfp == NULL)
    {
      perror("open:");
      exit(-1);
    }
    map<string,int> map1;
    char buf[1024];
    char *find;
    bzero(buf,sizeof(buf));
    while (fgets(buf,1024,rfp))
    {     
      find = strchr(buf,'\n');
      if (find)
      {
      *find = '\0';
      }
     if (map1.find(buf) == map1.end())//map容器中没有该元素
     {
       map1[buf] = 1;
     }
     else
     {
       map1[buf] = map1[buf] + 1;
     }
     bzero(buf,sizeof(buf));
    }
     fclose(rfp);
     map<int,string> map_sort;
     map<string,int>::iterator it;
     for (it = map1.begin();it != map1.end();it++)
     {
       map_sort[it->second] = it->first;
     }
     map<int,string>::iterator point;
     point = map_sort.end();
     --point;
     bzero(savestring,sizeof(savestring));
     strcpy(savestring,(point->second).c_str());
     return point->first;
}

int main(int argc, char const *argv[])
{
	  int pstr[N] = {0};//初始化
    char filename[20] = {'\0'};
    char savestring[20] = {'\0'};
    char maxstring[20] = {'\0'};
    int maxcount = 0;
    int savecount = 0;
	  time_t start ;
    time(&start);//起始时间
    hashtable<string> hash1(hash_fun);
    DownloadDataToHash("40w随机数据.txt",hash1);
    DealData(pstr,hash1);
    int i = 0;
    for (i = 0; i < N; i++)
    {
      if (pstr[i] == 0)
      {
        break;
      }
      sprintf(filename,"a%d.dat",pstr[i]);
      savecount = findMaxCount(filename,savestring);
      if (maxcount <= savecount)
      {
         bzero(maxstring,sizeof(maxstring));
         strcpy(maxstring,savestring);
         maxcount = savecount;
      }
      bzero(filename,sizeof(filename));
    }
    cout<<"出现次数最多的数:"<<maxstring<<endl;
    cout<<"出现次数:"<<maxcount<<endl;
    time_t end ;
    time(&end);//结束时间
    cout<<"程序用时为:"<<end-start<<"秒"<<endl;
    system("rm -f *.dat");
	  return 0;
}
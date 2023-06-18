#include<iostream>

#include<string.h>
#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>

using namespace std;

int rec_flag=0,no=0;
char rec_ind[5];

struct record
{
  char age[5],ind[5];
  char  usn[20],name[20],branch[5];

  char sem[5];
}rec[20];

struct index
{
    char usn[20],ind[20];
}in[20],temp;

void sort_index()
{
    int i,j;
    for(i=0;i<no-1;i++)
    for(j=0;j<no-i-1;j++)
    if(strcmp(in[j].usn,in[j+1].usn)>0)
    {
       temp=in[j];
       in[j]=in[j+1];
       in[j+1]=temp;
    }

}

void retrive_record(char *ind)
{
    for(int i=0;i<no;i++)
    {
      if(strcmp(rec[i].ind,ind)==0)
      {
      strcpy(rec_ind,ind);
      rec_flag=1;
      cout<<"\n record found:";
      cout<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
      return;
      }
    }
}


int search_index(char *usn)
{
      int flag=0;
      for(int i=0;i<no;i++)
      {
	  if(strcmp (in[i].usn,usn)==0)
	  {
	     retrive_record(in[i].ind);
	     flag=1;
	  }
      }
      if(flag)
	  return 1;
      else
	  return -1;
}

int search_usn(char *usn,int j)
{
      int flag=0;
      for(int i=0;i<j;i++)
      {
	  if(strcmp (rec[i].usn,usn)==0)
	  {
	     flag=1;break;
	  }
      }
      if(flag)
	  return 1;
      else
	  return -1;
}

void delet(char *st_usn)
{
      rec_flag=0;
      int fr=0;
      search_index(st_usn);
      if(!rec_flag)
      {
	 cout<<"\n deletion failed record not found";
	 return;
      }
      for(int i=0;i<no;i++)
      {
	 if(strcmp(rec[i].ind,rec_ind)==0)
	  {   fr=i; break;}
      }
      for(int i=fr;i<no-1;i++)
      {
	 rec[i]=rec[i+1];
	 char str[3];
	 //itoa(i,str,10);
	sprintf(str,"%d",i);
	 strcpy(rec[i].ind,str);
      }
      no--;
      fstream f1,f2;
      f1.open("record1.txt",ios::out);
      f2.open("index.txt",ios::out);
      for(int i=0;i<no;i++)
      {
      strcpy(in[i].usn,rec[i].usn);
      strcpy(in[i].ind,rec[i].ind);
      }
      sort_index();
      for(int i=0;i<no;i++)
      {
      f1<<rec[i].ind<<"|"<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
      f2<<in[i].usn<<"|"<<in[i].ind<<"\n";
      }
      f1.close();
      f2.close();
      cout<<"\n deletion successful\n";
}

int main()
{
      fstream file1,file3;
      int choice;
      char ind[5],st_usn[20],name[20],age[5],sem[5],branch[5],usn[20];
      int i;
 
      for(;;)
      {
      cout<<"\nchose\n1:add\n2:search\n3:delete\n4:display\n5:exit\n";
      cin>>choice;
      switch(choice)
      {
	 case 1:{
		file1.open("record1.txt",ios::app|ios::out);
		if(!file1)
		{
		  cout<<"File creation error\n";
		  exit(0);
		}
		int n;
		cout<<"enter no of students\n";
		cin>>n;
		cout<<"enter the details\n";
		for(i=no;i<no+n;i++)
		{
		  cout<<"\nenter "<<i+1<<" student:";

		  cout<<"\nusn:";
		  cin>>rec[i].usn;
		  cout<<"\nname:";
		  cin>>rec[i].name;
		  cout<<"\nage:";
		  cin>>rec[i].age;
		  cout<<"\nsem:";
		  cin>>rec[i].sem;
		  cout<<"\nbranch:";
		  cin>>rec[i].branch;
		  int q=search_usn(rec[i].usn,i);
		    
		file1<<i<<"|"<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
	       }
	       file1.close();
	       no=no+n;
	       fstream file1,file2;
	       file2.open("index1.txt",ios::out);
	       file1.open("record1.txt",ios::in);
	       for(i=0;i<no;i++)
	       {
		  file1.getline(ind,5,'|');
		  file1.getline(usn,20,'|');
		  file1.getline(name,20,'|');
		  file1.getline(age,5,'|');
		  file1.getline(sem,5,'|');
		  file1.getline(branch,5,'\n');
		  strcpy(rec[i].ind,ind);
		  strcpy(in[i].usn,usn);
		  strcpy(in[i].ind,ind);
	       }
	       sort_index();
	       cout<<"\nafter sorting index file contents are\n";
	       for(i=0;i<no;i++)
	       cout<<in[i].usn<<" "<<in[i].ind<<endl;
	       for(i=0;i<no;i++)
	       {
		   file2<<in[i].usn<<"|"<<in[i].ind<<"\n";
	       }
	       file1.close();
	       file2.close();
	       break;
		}
	 case 2:{
		cout<<"\nEnter usn of stu whose rec is to be displayed\n";
		cin>>st_usn;
		int q=search_index(st_usn);
		if(q==1)
		   cout<<"\nsearch sucessful\n";
		else
		   cout<<"\nnt successful\n";
		break;
		}
	 case 3:{
		cout<<"Enter usn of stu whose rec is to be del\n";
		cin>>st_usn;
		delet(st_usn);
		break;
		}
	 case 4:{
	      fstream f1;
	      f1.open("record1.txt",ios::in);
	      if(!f1)
	      {
	      cout<<"err\\\\\\\\\\\\\\\\n";
	      exit(0);
	      }
	      int i=0;
	      while(i!=no)

	       {
		  f1.getline(ind,5,'|');
		  f1.getline(usn,20,'|');
		  f1.getline(name,20,'|');
		  f1.getline(age,5,'|');
		  f1.getline(sem,5,'|');
		  f1.getline(branch,5,'\n');
		  cout<<"usn:"<<usn<<"\t"<<"name:"<<name<<"\t"<<"sem:"<<sem<<"\t"<<"branch:"<<branch<<"\t"<<"age:"<<age<<"\t"<<endl;
		  i++;
	       }
		  break;
		}
	case 5:{
		 cout<<"\n ending program";
		
		 exit(0);
		}
	 default:
		 cout<<"\nInvalid\n";
		 break;
	 }
     }
}

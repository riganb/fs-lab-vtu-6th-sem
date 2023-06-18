#include<iostream>


#include<string.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

char rec_ind[5];
int rec_flag=0;

struct record
{
	char age[5],ind[5];
	char name[20],usn[20],branch[5];
	char sem[5];
}rec[20];

struct secind
{
	char name[20],usn[20],ind[20];
}sec[20],found[20];

struct index
{
	char usn[20],ind[20];
}in[20],temp;

int no=0;

void sort_index()
{
	int i,j;
	//index temp;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(in[j].usn,in[j+1].usn)>0)
	{
		temp=in[j];
		in[j]=in[j+1];
		in[j+1]=temp;
	}
}

void sort_secindex()
{
	int i,j;
	secind temp;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(sec[j].name,sec[j+1].name)>0)
	{
		temp=sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
	else if(strcmp(sec[j].name,sec[j+1].name)==0)
	{
		 if(strcmp(sec[j].usn,sec[j+1].usn)>0)
		 {
		     temp=sec[j];
		     sec[j]=sec[j+1];
		     sec[j+1]=temp;
		 }
	}
}

void retrive_record(char *ind)
{
	int flag=0;
	for(int i=0;i<no;i++)
	{
		if(strcmp(rec[i].ind,ind)==0)
		{
			strcpy(rec_ind,ind);
			rec_flag=1;
			cout<<"\n record found:";
			cout<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"record search failed";
	}
}

void search_index(char *usn)
{
	int flag=0;
	for(int	i=0;i<no;i++)
	{
		if(strcmp(in[i].usn,usn)==0)
		{
			retrive_record(in[i].ind);
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"index search failed\n";
	}
}

void search(char *st_name)
{
	char st_usn[20];
	int flag1=0;
	int k=0,i;
	for(i=0;i<no;i++)
	{
		if(strcmp(sec[i].name,st_name)==0)
		{
			strcpy(found[k].usn,sec[i].usn);
			strcpy(found[k].name,sec[i].name);
			strcpy(found[k].ind,sec[i].ind);
			flag1=1;
			k++;
		}
	}
	if(!flag1)
	{
		cout<<"sec ind search failed\n";
		return;
	}
	cout<<"\n records matching are:";
	for(i=0;i<k;i++)
	cout<<"\n"<<found[i].name<<" "<<found[i].usn;
	cout<<"\n choose an usn: ";
	cin>>st_usn;
	flag1=0;
	for(i=0;i<k;i++)
		if(strcmp(found[i].usn,st_usn)==0)
		{
			search_index(st_usn);
			flag1=1;
		}
	if(!flag1)
	{
		cout<<"wrong usn search failed\n";
	}
}


int srch_usn(char *usn,int j)
{
int flag=0;
for(int i=0;i<j;i++)
if(strcmp(rec[i].usn,usn)==0)
{
flag=1;
}
if(flag)
return 1;
else
return -1;
}

void delet(char *st_name)
{
	rec_flag=0;
	int fr=0;
	search(st_name);
	if(!rec_flag)
	{
		cout<<"\ndeletion faild record not found";
		return;
	}
	for(int i=0;i<no;i++)
	{
		if(strcmp(rec[i].ind,rec_ind)==0)
			{
			fr=i;
			break;
			}
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

	fstream f1,f2,f3;
	f1.open("record.txt",ios::out);
	f2.open("index.txt",ios::out);
	f3.open("secindex.txt",ios::out);
	for(int i=0;i<no;i++)
	{
	strcpy(sec[i].name,rec[i].name);
	strcpy(sec[i].usn,rec[i].usn);
	strcpy(in[i].usn,rec[i].usn);
	strcpy(sec[i].ind,rec[i].ind);
	strcpy(in[i].ind,rec[i].ind);

	}
	sort_index();
	sort_secindex();
	for(int i=0;i<no;i++)
	{
		f1<<rec[i].ind<<"|"<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
		f2<<in[i].usn<<"|"<<in[i].ind<<"\n";
		f3<<sec[i].name<<"|"<<sec[i].usn <<"|"<<sec[i].ind<<"\n";
	}

	f1.close();
	f2.close();
	cout<<"\n deletion successful\n";
}

main()
{
	fstream file1,file2,file3;
	int choice;
	char rt_usn[20],st_name[20],st_usn[20],ind[5],name[20],age[5],sem[5],branch[5],usn[20];
	int i,flag1,flag;
	
	file3.open("index.txt",ios::out);
	file1.open("record.txt",ios::out);
	file2.open("secindex.txt",ios::out);
	file3.close();
	file1.close();
	file2.close();
	for(;;)

       {		cout<<"chose\n1:add\n2:search\n3:delete\n4:display\n5:exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				{
				file3.open("index.txt",ios::out);
				file1.open("record.txt",ios::app);
				file2.open("secindex.txt",ios::out);
				int n;
				cout<<"Enter no of students\n";
				cin>>n;
				cout<<" Enter the details\n";
				for(i=no;i<no+n;i++)
				{
			  label:	cout<<"\nenter "<<i+1<<" student:";
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
					int q=srch_usn(rec[i].usn,i);
					if(q==1)
					{
					cout<<"duplicate val enter again\n";
					goto label;
					}
					file1<<i<<"|"<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].age<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";


				 }
				file1.close();
				no=no+n;
				file1.open("record.txt",ios::in);
				for(i=0;i<no;i++)
				{
					file1.getline(ind,5,'|');
					file1.getline(usn,20,'|');
					file1.getline(name,20,'|');
					file1.getline(age,5,'|');
					file1.getline(sem,5,'|');
					file1.getline(branch,5,'\n');
					strcpy(rec[i].ind,ind);
					strcpy(sec[i].ind,ind);
					strcpy(in[i].ind,ind);
					strcpy(sec[i].name,name);
					strcpy(sec[i].usn,usn);
					strcpy(in[i].usn,usn);
				}

				sort_index();
				sort_secindex();
				cout<<"after sortin secindex file contents are\n";
				for(i=0;i<no;i++)
				cout<<sec[i].name<<" "<<sec[i].usn<<" "<<sec[i].ind<<endl;
				cout<<"after sortin index file contents are\n";
				for(i=0;i<no;i++)
				cout<<in[i].usn<<" "<<in[i].ind<<endl;
				for(i=0;i<no;i++)
				{
					file2<<sec[i].name<<"|"<<sec[i].usn<<"|"<<sec[i].ind<<"\n";
					file3<<in[i].usn<<"|"<<in[i].ind<<"\n";
				}
				file1.close();
				file2.close();
				file3.close();
				break;
				}
			case 2:
				{
				cout<<"Enter name of stu whose rec is to be displayed\n";
				cin>>st_name;
				search(st_name);
				break;
				}
			case 3:
				{
				cout<<"Enter name of stu whose rec is to be del\n";
				cin>>st_name;
				delet(st_name);

				break;
				}
			case 4:
				{
				fstream file1;
				file1.open("record.txt",ios::in);
			   cout<<"USN\t NAME\t AGE\t SEM\t BRANCH\n";
				while(!file1.eof())
				{

					file1.getline(ind,5,'|');
					file1.getline(usn,20,'|');
					file1.getline(name,20,'|');
					file1.getline(age,5,'|');
					file1.getline(sem,5,'|');
					file1.getline(branch,5,'\n');
			     cout<<usn<<"\t"<<name<<"\t"<<age<<"\t"<<sem<<"\t"<<branch<<"\n";
			     }
			     file1.close();
			     break;
				}
			case 5:
				{
				cout<<"\n ending program";
				
				exit(0);
				}			
			default:
				{
				cout<<"Invalid\n";
				break;
				}
		}
	}
}

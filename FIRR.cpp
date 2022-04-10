#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
fstream fp,fa,fs;
class fir
{
 char naoi[20];
 char addi[20];
 char noi[11];
 char place_occ[30];
 char offence[20],prop[20],sus[20],comp[200];
 char status[20];
 char d[10],h[5];
 public:
  void regfir();
  void showfir();
  char* retsus()
  {return sus;}
  char* retnamei()
  {return naoi;}
  char* retcomp()
  {return comp;}
}f;


char* passw()
{
     char pass[32];
    int i = 0;
    char a;
    for(i=0;;)
    {
    a=getch();
    if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
    {
    pass[i]=a;
    ++i;
    cout<<"*";
    }
    if(a=='\b'&&i>=1)
    {
    cout<<"\b \b";
    --i;
    }
    if(a=='\r')
    {
    pass[i]='\0';
    break;
    }
    }
    return pass;
}
class account
{ char name[20];
  char password[20];
  public:
  void read();
  void take(char acco[]);
  char* retname()
  {return name;}
  char* retpass()
  {return password;}
}A;
  void account::take(char acco[20])
  {
   char pass[20];
   strcpy(name,acco);
   START:
   cout<<"\nEnter Password  :";
   strcpy(password,passw());
   cout<<"\nConfirm Your Password  :";
   strcpy(pass,passw());
   if(strcmp(password,pass)==0)
   cout<<"\n\n\t\t\t\tPASSWORD MATCHED"<<endl;
   else
   {
   cout<<"\n\n\t\t\t     PASSWORD DID NOT MATCHED"<<endl;
   goto START;
   }
  }
char c(char acc[20],char pass[20])
{
char found='N';
fstream f;
f.open("accounts.dat",ios::in|ios::binary);
if(!f)
{
cout<<"\n\t\t\tFILE READING ERROR";
getch();
}
  while(f.read((char*)&A,sizeof(account)))
  {
    if((strcmpi(A.retname(),acc)==0)&&(strcmpi(A.retpass(),pass)==0))
    {
    clrscr();
    cout<<"\n\t\t\t    YOUR ACCOUNT IS FOUND\n";
    getch();
    found='Y';
    break;
    }
  }
  if(found=='N')
  {
  cout<<"\n\t\t\t    NO SUCH ACCOUNT WAS FOUND \n";
  getch();
  }
  return found;
}

class suspects
{ char name[20];
  char crime[20];
  public:
  char* retname()
  {return name;}
}S;

char check(char temp[20])
{
      char ch='Y',temp1[20];
      fa.open("accounts.dat",ios::binary|ios::in);
      while(fa.read((char*)&A,sizeof(A)))
      {
	if(!fa)
	{
	cout<<"file error"<<endl;
	getch();
	}
	strcpy(temp1,A.retname());
	if(strcmp(temp1,temp)==0)
	{
	cout<<"\n\t     THIS ACCOLUNT NAME ALREADY EXIST TRY ANOTHER ONE\n";
	ch='N';
	break;
	}
      }
      fa.close();
      return ch;
}

void account::read()
{
    char temp_pass[20],temp_acc[20],ch;
    ACC:
    cout<<"\nEnter Your Account Name : ";
    gets(temp_acc);
    ch=check(temp_acc);
    if(ch=='Y')
    strcpy(name,temp_acc);
    else
    goto ACC;
    START:
    cout<<"\nEnter Password  : ";
    strcpy(password,passw());
    cout<<"\nConfirm Your Password  :";
    strcpy(temp_pass,passw());
    if(strcmp(password,temp_pass)==0)
    cout<<"\n\n\t\t\t\tPASSWORD COMFIRMED"<<endl;
    else
    {
    cout<<"\n\n\t\t\t     PASSWORD NOT CONFIRMED"<<endl;
    goto START;
    }
}
void create_account()
{
  A.read();
  fa.open("accounts.dat",ios::binary|ios::app);
  fa.write((char*)&A,sizeof(A));
  fa.close();
  cout<<"\n\n \t\t   YOUR ACCOUNT HAS BEEN SUCCESSFULLY CREATED";
}
void change_password()
{
  fstream f;
  char acc[20],pass[20],temp[20];
  STAR:
  fa.open("accounts.dat",ios::binary|ios::in);
  f.open("temp.dat",ios::binary|ios::out);
  cout<<"\t ENTER THE ACCOUNT NAME OF WHICH YOU WANT TO CHANGE THE PASSWORD OF\n";
  cout<<"\t\t\t\t  ";
  gets(acc);
  UJJ:
  cout<<"\n\t\t\tEnter The Password  :";
  strcpy(pass,passw());
  cout<<"\n\t\t\tConfirm Your Password  :";
  strcpy(temp,passw());
  if(strcmp(pass,temp)==0)
  cout<<"\n\t\t\t\tPASSWORD CONFIRMED";
  else
  {
  cout<<"\n\t\tPASSWORD NOT CONFIRMED\n";
  getch();
  goto UJJ;
  }
  getch();
  char ch=c(acc,pass);
  if(ch=='Y')
  {
  while(fa.read((char*)&A,sizeof(A)))
  {
    if(strcmp(A.retname(),acc)!=0)
    {
     f.write((char*)&A,sizeof(A));
    }
    else if(strcmp(A.retname(),acc)==0)
    {
     clrscr();
     cout<<"\nACCOUNT FOUND\n";
     cout<<"Account Name is  :"<<A.retname();
     cout<<"\nPassword is  :"<<A.retpass();
    }
  }
  }
  else
  {
  cout<<"\n\t\t  NO SUCH ACCOUNT FOUND\n";
  getch();
  goto STAR;
  }
  fa.close();
  f.close();
  remove("accounts.dat");
  f.open("temp.dat",ios::binary|ios::app);
  A.take(acc);
  f.write((char*)&A,sizeof(A));
  f.close();
  int x;
  x=rename("temp.dat","accounts.dat");
  if(x==0)
  cout<<"PASSWORD SUCCESSFULLY CHANGED"<<endl;
}

void check_sus()
{  int found=0;
  fs.open("Criminal_Records.dat",ios::binary|ios::in);
  while(fs.read((char*)&S,sizeof(S)))
    {   if(strcmp(S.retname(),f.retsus())==0)
	 {cout<<"\n\n % SUSPECT HAS BEEN FOUND HAVING PREVIOUS CRIMINAL RECORD";
	  cout<<"\n      IT WILL FASTEN OUR PROGRESS\n\n";
	 found=1;
	 break;
	 }
    }
    if(found==0)
    cout<<"\n\n % THE SUSPECT HAS NO PREVIOUS CRIMINAL RECORD\n";
  fs.close();
}

void fir::regfir()
{ cout<<" \n 1. GIVE DETAILS OF ACCUSED \n";
 cout<<" \t  Name :";
 gets(naoi);
 cout<<"\n \t Address :";
 gets(addi);
 do
{ cout<<"\n \t Phone Number :";
  gets(noi);
  if(strlen(noi)!=10)
  cout<<"\n\t\tPLEASE ENTER A VALID NUMBER !!!";
}while(strlen(noi)!=10);
 cout<<"\n\n 2. PLACE OF OCCURRENCE :";
 gets(place_occ);
 cout<<"\n\n 3.DATE AND HOUR OF THE OCCUERRENCE \n date(dd/mm/yy) :";
 gets(d);
 cout<<" hour(am/pm):";
 gets(h);
 cout<<"\n\n 4.OFFENCE ( murder,rape,theft,etc.) :";
 gets(offence);
 if(strcmp(offence,"theft")==0)
 {
  cout<<"\n property stolen :";
  gets(prop);
 }
 cout<<"\n 5.NAME OF SUSPECT (if any) :";
 gets(sus);
 clrscr();
 cout<<"\n 6.WHOLE COMPLAINT IN DETAIL:\n";
 gets(comp);
}
void regisfir()
{  fp.open("info_fir.dat",ios::out|ios::binary|ios::app);
   f.regfir();
   fp.write((char*)&f,sizeof(f));
   fp.close();
   clrscr();
   cout<<"\n YOUR FIR HAS BEEN REGISTERED IN THE NAME OF "<<f.retnamei();
   check_sus();
   cout<<"\n WE WILL TRY TO SOLVE THIS CASE AS SOON AS POSSIBLE";
}

void gun()
{
char a=219,b=220,c=223,e=222,f=92;
cout<<"\n\n\n\n\n\n";
   cout<<"\n\t\t\t\t      "<<b;
   cout<<"\n\t";
   cout<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b;
   {
   cout<<"\n\t";
   cout<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<c;
   cout<<"\n\t ";
   for(int i=0;i<=5;i++)
   {cout<<a<<a<<a<<a<<a<<a<<a;
    if(i==0)
    cout<<" "<<f<<f<<"   "<<e;
    if(i==1)
    cout<<"   "<<f<<f<<" "<<e;
    if(i==2)
    cout<<c<<c<<c<<c<<c<<c<<c;
    cout<<"\n\t ";
   }
   }
}

void fir::showfir()
{cout<<" \n 1. DETAILS OF ACCUSED \n";
 cout<<" \t  Name :";
 cout<<naoi;
 cout<<"\n \t Address :";
 cout<<addi;
 cout<<"\n \t Phone Number :";
 cout<<noi;
 cout<<"\n\n 2. PLACE OF OCCURRENCE :";
 puts(place_occ);
 cout<<"\n\n 3.DATE AND HOUR OF THE OCCUERRENCE \n date(dd/mm/yy) :";
 puts(d);
 cout<<" hour(am/pm):";
 puts(h);
 cout<<"\n\n 4.OFFENCE ( murder,rape,theft,etc.) :";
 puts(offence);
 if(strcmp(offence,"theft")==0)
 {
  cout<<"\n property stolen :";
  puts(prop);
 }
   if(strcmp(sus,"no one")!=0)
   {cout<<"\n 5.NAME OF SUSPECT :";
   puts(sus);
   }
 getch();
 clrscr();
 cout<<"\n 6.WHOLE COMPLAINT IN DETAIL:";
 puts(comp);
}

void display_all()
{ fp.open("info_fir.dat",ios::binary|ios::in);
     while(fp.read((char*)&f,sizeof(f)))
	{ clrscr();
	  f.showfir();
	  getch();
	}
fp.close();
}
void read_fir()
{  char name[20];
   int find=0;
   cout<<"\n PLEASE GIVE THE NAME IN WHOSE THE FIR HAS BEEN REGISTERED 'OR' TYPE All TO VIEW ALL THE FIRs : ";
   gets(name);
   if(strcmpi(name,"all")==0)
       { display_all();
       }
   else
     {
       fp.open("info_fir.dat",ios::binary|ios::in);
       while(fp.read((char*)&f,sizeof(f)) && find==0)
       {
	 if(strcmp(name,f.retnamei())==0)
	   { clrscr();
	     f.showfir();
	     find=1;
	   }
	}
       if(find==0)
	{ cout<<"\n FIR NOT FOUND!";
	  getch();
	}
    }
}

void add_detail(char name[])
{  int rec_count=0,flag=0;
   char temp_comp[200];
   fp.open("info_fir.dat",ios::binary|ios::out|ios::in);
   fp.seekg(0,ios::beg);
   while(fp.read((char*)&f,sizeof(f)) && flag==0)
   {    if(strcmp(f.retnamei(),name)==0)
	 {  flag=1;
	    cout<<"ENTER THE MODIFIED COMPLAINT : ";
	    gets(temp_comp);
	    strcpy(f.retcomp(),temp_comp);
	    fp.seekp(rec_count*sizeof(f),ios::beg);
	    fp.write((char*)&f,sizeof(f));
	  }
	  rec_count++;
    }
   fp.close();
  if(flag==1)
  cout<<"\n\n\t\t...THANK YOU FOR YOUR COOPERATION \n\n\t\t   THE FIR HAS BEEN MODIFIED";
  getch();
}
void add_suspect(char name[])
{  int rec_count=0,flag=0;
   char temp[20],temp_sus[20]=" , ";
   fp.open("info_fir.dat",ios::binary|ios::out|ios::in);
   fp.seekg(0,ios::beg);
   while(fp.read((char*)&f,sizeof(f)) && flag==0)
   {    if(strcmp(f.retnamei(),name)==0)
	 {  flag=1;
	    cout<<"\n ENTER THE NAME OF THE PERSON YOU SUSPECT : ";
	    gets(temp);
	    strcat(temp_sus,temp);
	    strcat(f.retsus(),temp_sus);
	    fp.seekp(rec_count*sizeof(f),ios::beg);
	    fp.write((char*)&f,sizeof(f));
	  }
	 rec_count++;
     }
   fp.close();
  if(flag==1)
  {cout<<"\n\n\t\t..THANK YOU FOR COOPERATION\n\n\t\t  SUSPECT HAS BEEN ADDED";
  }
getch();
}


void modify_fir()
{AGAIN:
 char name[20],op;
 int flag=0,rec=0;
 cout<<"\nPLEASE ENTER THE NAME IN WHOSE THE FIR IS REGISTERED\n\n - ";
 gets(name);
 fp.open("info_fir.dat",ios::binary|ios::in);
 fp.seekp(rec,ios::beg);
 while(fp.read((char*)&f,sizeof(f)) && flag==0)
   {
    if(strcmp(f.retnamei(),name)==0)
	{ flag=1;
	}
    }
 fp.close();
 if(strcmp(name,"exit")==0)
 exit(0);
 if(flag==0)
 { cout<<"\n FIR NOT FOUND!";
 goto AGAIN;
 }
 cout<<"\nNOW SELECT AN OPTION";
 cout<<"\n 1.ADDING DETAIL TO THE COMPLAINT";
 cout<<"\n 2.TO ADD ANY SUSPECT\n";
 op=getche();
    switch(op)
     { case '1': clrscr();
		 add_detail(name);
		 break;
	case '2': clrscr();
		 add_suspect(name);
		 break;
      }
   }

void delete_fir()
{char name[20];
 cout<<"PLEASE GIVE THE NAME IN WHOSE THE FIR IS REGISTERED";
 gets(name);
fstream fp1;
fp.open("info_fir.dat",ios::in|ios::binary|ios::out);
    fp1.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&f,sizeof(f)))
	{
	 if(strcmp(f.retnamei(),name)!=0)
		{
		 fp1.write((char*)&f,sizeof(f));
		 }
	 }
    fp1.close();
    fp.close();
    remove("info_fir.dat");
    rename("Temp.dat","info_fir.dat");
    cout<<"\n\n\tFIR Deleted ..";
}


void del_acc()
{
  fstream f;
  char acc[20],pass[20],temp[20];
  STAR:
  fa.open("accounts.dat",ios::binary|ios::in);
  f.open("temp1.dat",ios::binary|ios::out);
  cout<<"\t ENTER THE ACCOUNT NAME THAT YOU WANT TO DELETE OFF!!!!!!!!!!\n";
  cout<<"\t\t\t\t  ";
  gets(acc);
  UJJ:
  cout<<"\n\t\t\tEnter The Password  :";
  strcpy(pass,passw());
  cout<<"\n\t\t\tConfirm Your Password  :";
  strcpy(temp,passw());
  if(strcmp(pass,temp)==0)
  {
  cout<<"\n\t\t\t\tPASSWORD CONFIRMED";
  getch();
  }
  else
  {
  cout<<"\n\t\tPASSWORD NOT CONFIRMED";
  getch();
  goto UJJ;
  }
  char ch=c(acc,pass);
  if(ch=='Y')
  {
  while(fa.read((char*)&A,sizeof(A)))
  {
    if(strcmp(A.retname(),acc)!=0)
    {
     f.write((char*)&A,sizeof(A));
    }
  }
  }
  else
  {
  cout<<"\n\t\tNO SUCH ACCOUNT FOUND\n";
  getch();
  goto STAR;
  }
  fa.close();
  f.close();
  remove("accounts.dat");
  int x;
  x=rename("temp1.dat","accounts.dat");
  if(x==0)
  cout<<"\n\t\tACCOUNT SUCCESSFULLY DELETED"<<endl;
}


void intro()
{
STAR:
clrscr();
char acc[20],pass[20],temp_pass[20];
cout<<"\nEnter Your ACCOUNT Name  :";
gets(acc);
fstream f;
char found='N';
f.open("accounts.dat",ios::in|ios::binary);
if(!f)
{
cout<<"\n\t\t\tFILE READING ERROR";
getch();
return;
}
  while(f.read((char*)&A,sizeof(account)))
  {
    if(strcmpi(A.retname(),acc)==0)
    {
    found='Y';
    break;
    }
  }
  if(found=='N')
  {
  cout<<"\n\t\t\t    NO SUCH ACCOUNT NAME WAS FOUND \n";
  getch();
  goto STAR;
  }
  f.close();
    START:
    cout<<"\nEnter Password  : ";
    strcpy(pass,passw());
    cout<<"\nConfirm Your Password  :";
    strcpy(temp_pass,passw());
    if(strcmp(pass,temp_pass)==0)
    cout<<"\n\n\t\t\t\tPASSWORD CONFIRMED"<<endl;
    else
    {
    cout<<"\n\n\t\t\t     PASSWORD NOT CONFIRMED"<<endl;
    goto START;
    }
getch();

found='N';
f.open("accounts.dat",ios::in|ios::binary);
if(!f)
{
cout<<"\n\t\t\tFILE READING ERROR";
getch();
return;
}
  while(f.read((char*)&A,sizeof(account)))
  {
    if((strcmpi(A.retname(),acc)==0)&&(strcmpi(A.retpass(),pass)==0))
    {
    clrscr();
    cout<<"\n\t    YOUR ACCOUNT IS FOUND WELCOME TO THE FIF REGISTRATION PRORAM\n";
    getch();
    found='Y';
    break;
    }
  }
  if(found=='N')
  {
  cout<<"\n\t\t\t    NO SUCH ACCOUNT WAS FOUND \n";
  getch();
  goto STAR;
  }
  f.close();
}

void firi()
{  int ch;
clrscr();
cout<<"\n\tPRESS 1. FOR REGISTRATION OF NEW FIR\n";
cout<<"\n\tPRESS 2. FOR READING ANY PREVIOUS FIR\n";
cout<<"\n\tPRESS 3. FOR MODIFYING AN FIR\n";
cout<<"\n\tPRESS 4. FOR DELETING AN FIR\n";
cout<<"\n\tPRESS 5. TO EXIT THE PROGRAM\n";
cout<<"\n\tNOW PLEASE ENTER YOUR CHOICE\n";
ch=getche();
switch(ch)
{ case '1': clrscr();
	  regisfir();
	  break;

  case '2': clrscr();
	  read_fir();
	  break;

  case '3': clrscr();
	  modify_fir();
	  break;

  case '4': clrscr();
	  delete_fir();
	  break;
  case '5':
	  exit(0);
}
getch();
}
void acci()
{ clrscr();
  char ch;
  cout<<"\n\t\t\t\t ACCOUNTING OPTIONS\n";
  cout<<"\n\t1.TO CREATE A NEW ACCOUNT\n";
  cout<<"\n\t2.TO CHANGE PASSWORD OF AN ACCOUNT\n";
  cout<<"\n\t3.TO DELETE AN ACCOUNT\n";
  cout<<"\n\t4.TO EXIT THE PROGRAM\n";
  cout<<"\n\tNOW PLEASE ENTER YOUR CHOICE\n";
  ch=getche();
  switch(ch)
  { case '1': clrscr();
	      create_account();
	      break;

    case '2': clrscr();
	      change_password();
	      break;

    case '3': clrscr();
	      del_acc();
	      break;
    case '4':
    exit(0);
    default:
    cout<<"\nINVALID OPTION";
  }
  getch();
  }

void main()
{
clrscr();
do{
char b=220;
int x=43,y=9;
char j[10];
   for(int k=0;k<=35;k++)
   {gun();
    cout<<"\t\t\t\tFIR";
    gotoxy(x,y);
    x++;
    cout<<b<<b<<b;
    delay(10);
    clrscr();
   }
}while(!kbhit());
getch();
clrscr();
char C,ch;
cout<<"\t\t     THIS IS THE FIR REGISTRATION PROGRAM\n\n\n";
UJJU:
cout<<"\n\n\tNOW PRESS 1. IF YOU WANT TO ACCESS TO THIS PROGRAM\n";
cout<<"\n\tOR  PRESS 2. TO EXIT THIS PROGRAM\n";
cout<<"\n\tPLEASE ENTER YOUR CHOICE NOW\n";
C=getche();
switch(C)
{
case '1':
   intro();
   break;
case '2':
   exit(0);
default:
   cout<<"\n\n\t\t\tINVALID OPTION\n";
   getch();
   clrscr();
   goto UJJU;
}
do
{clrscr();
cout<<" \n \t\t\t\t\t MAIN MENU \n";
cout<<"\n\n\n \t 1. ACCOUNT RELATED ISSUES\n";
cout<<"\n\t 2.FOR FIR RELATED ISSUES\n";
cout<<"\n\t 3.TO EXIT THE PROGRAM\n";
cout<<"\n\t NOW PLEASE ENTER YOUR CHOICE\n";
ch=getche();
switch(ch)
{ case '1': clrscr();
	   acci();
	  break;
  case '2': clrscr();
	  firi();
	  break;
  case '3': exit(0);
	  break;
}
}while(ch!='3');

 }
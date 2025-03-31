#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int mon[]={31,28,31,30,31,30,31,31,30,31,30,31};
bool validityslsh(string s)  // backslash validity checker
{
    bool check=false;
    int count=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='/')
        count++;
    }
    if(count!=2)
    return false;
    count=0;
    return true;
}

bool validityday(int x, int y)
{ 
  if (x<=mon[y-1] && x>0)
  return true;
  return false;
}

bool validitymon(int x)
{
  if (x>0 && x<=12)
  return true;
  return false;
}

bool validityyear(int x)
{
    if (x>0){
      if (x%4==0)
      mon[1]=29;
      return true;
    }
    mon[1]=28;
    return false;
}

class DateInput
{
    public:
    string date; //inputed date is in the string format [DD/MM/YYYY]
    int day;  
    int month;
    int year;
    DateInput()
    {
        day=0;
        month=0;
        year=0;
    }
    void input()
    {
      cin  >> date;
      if(!validityslsh(date) || !(date.size()>=5))
      {
        do
        {
            cout << "Invalid! Please re-enter." <<endl;
            cin >> date;
        }while(!validityslsh(date) || !(date.size()>=5));
      }
    }
    void convert()
    { int slsh1=0; //index of slash1
      int slsh2=0; //index of slash2
      slsh1=date.find_first_of("/");
      slsh2=date.find_last_of("/");
      //cout << slsh1 << endl <<slsh2 << endl << date.size() <<endl;
      if (slsh1==slsh2 or slsh2==date.size()-1 or slsh1==0)
      {
        cout << "Invalid Date! Please re-enter the date." << endl;
        DateInput::input();
      }
      day=stoi(date.substr(0,slsh1));
      month=stoi(date.substr(slsh1+1,slsh2-slsh1-1));
      year=stoi(date.substr(slsh2+1,date.size()-slsh2-1));
      if (!validityyear(year))
      {
        do{
          cout << "Invalid YYYY. [" << year << "] Please re-enter the YYYY." << endl;
          cin >> year;
        }
        while(!validityyear(year));
      }
      if (!validitymon(month))
      {
        do{
          cout << "Invalid MM. [" << month << "] Please re-enter the MM." << endl;
          cin >> month;
        }
        while(!validitymon(month));
      }
      if (!validityday(day,month))
      {
        do{
          cout << "Invalid DD. [" << day << "] Please re-enter the DD." << endl;
          cin >> day;
        }
        while(!validityday(day,month));
      }
    }
};

class DateCalculation
{
  public:
  int days;
  int months;
  int years;
  int dayst;
  int count;
  DateCalculation()
  {
    days=0;
    months=0;
    years=0;
    dayst=0;
    count=0;
  }
  void calculate(DateInput& obj1, DateInput& obj2)
  { 
    count=0; // counts the no of leap years
    for(int i=obj1.year;i<=obj2.year;i++)
    { if (i%4==0)
      {
        mon[1]=29;
        count++;
      }
      else
        mon[1]=28;
        int monlimit=(i==obj2.year)?obj2.month:12;
        int monstart=(i==obj1.year)?obj1.month:1;
        for(int j=monstart;j<=monlimit;j++)
        { if(j==obj1.month && i==obj1.year)
          {
          days=days+(mon[j-1]-obj1.day);
          dayst=dayst+(mon[j-1]-obj1.day);
          }
          else if(j==obj2.month && i==obj2.year)
          {
          days=days+obj2.day;
          dayst=dayst+obj2.day;
          }
          else
          {
          days=days+mon[j-1];
          dayst=dayst+mon[j-1];
          }
          if(dayst>=mon[j-1])
          {
            months+=1;
            dayst=dayst-mon[j-1];
          }
        }
        if(months>=12)
        {
        years+=1;
        months=months-12;
        }

    }
  }
  

  void display()
  {
    cout << "\n\n-----Output-----\n\n";
    cout << "Number of days lived : " << days << endl;
    
    if (years) cout << years << " years ";
    if(months) cout << months << " months ";
    if (dayst) cout << dayst << " days ";
    cout << "old" << endl;

  }
    
 
};
int main()
{
  DateInput o1; //date of birth
  DateInput o2; //current date
  cout << "Enter the date of birth [DD/MM/YYYY] :" << endl;
  o1.input();
  o1.convert();
  cout << "Enter today's date [DD/MM/YYYY] :" <<endl;
  o2.input();
  o2.convert();
  DateCalculation o3;
  o3.calculate(o1,o2);
  o3.display();
  return 0;
}
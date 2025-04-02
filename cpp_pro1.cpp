#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Leap year check
bool isLeapYear(int year) {
    // A year is a leap year if it is divisible by 4 but not by 100,
    // except if it is divisible by 400.
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Checks if the date string has exactly two slashes
bool validityslsh(string s) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '/')
            count++;
    }
    return (count == 2);
}

// Return the number of days in a given month/year
int daysInMonth(int month, int year) {
    int monArr[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return monArr[month - 1];
}

bool validityday(int x, int month, int year) { 
    if (x > 0 && x <= daysInMonth(month, year))
        return true;
    return false;
}

bool validitymon(int x) {
    return (x > 0 && x <= 12);
}

bool validityyear(int x) {
    return (x > 0);
}

class DateInput {
public:
    string date; // Input date in the format [DD/MM/YYYY]
    int day;  
    int month;
    int year;
    
    DateInput() : day(0), month(0), year(0) { }
    
    void input() {
        cin >> date;
        while (!validityslsh(date) || date.size() < 5) {
            cout << "Invalid! Please re-enter." << endl;
            cin >> date;
        }
    }
    
    void convert() { 
        int slsh1 = date.find_first_of("/");
        int slsh2 = date.find_last_of("/");
        
        if (slsh1 == slsh2 || slsh1 == 0 || slsh2 == date.size()-1) {
            cout << "Invalid Date! Please re-enter the date." << endl;
            input();
            convert();
            return;
        }
        
        day = stoi(date.substr(0, slsh1));
        month = stoi(date.substr(slsh1 + 1, slsh2 - slsh1 - 1));
        year = stoi(date.substr(slsh2 + 1, date.size() - slsh2 - 1));
        
        while (!validityyear(year)) {
            cout << "Invalid YYYY. [" << year << "] Please re-enter the YYYY." << endl;
            cin >> year;
        }
        while (!validitymon(month)) {
            cout << "Invalid MM. [" << month << "] Please re-enter the MM." << endl;
            cin >> month;
        }
        while (!validityday(day, month, year)) {
            cout << "Invalid DD. [" << day << "] Please re-enter the DD." << endl;
            cin >> day;
        }
    }
};

class DateCalculation {
public:
    int days;
    int months;
    int years;
    int dayst; // remaining days after full months
    int count;
    
    DateCalculation() : days(0), months(0), years(0), dayst(0), count(0) { }
    
    // This function calculates the difference between two dates.
    void calculate(DateInput& start, DateInput& end) { 
        // Loop through each year from the start year to the end year
        for (int y = start.year; y <= end.year; y++) {
            int startMonth = (y == start.year) ? start.month : 1;
            int endMonth = (y == end.year) ? end.month : 12;
            for (int m = startMonth; m <= endMonth; m++) {
                // same year and same month both the dates
                if (startMonth==endMonth && start.year==end.year)
                {
                    int diff = end.day-start.day;
                    days+=diff;
                    dayst+=diff;
                    break;
                }
                if (y == start.year && m == start.month) {
                    // Add days from the start day to the end of the month
                    int diff = daysInMonth(m, y) - start.day;
                    days += diff;
                    dayst += diff;
                }
                else if (y == end.year && m == end.month) {
                    // Add days from the beginning of the month to the end day
                    days += end.day;
                    dayst += end.day;
                }
                else {
                    int d = daysInMonth(m, y);
                    days += d;
                    dayst += d;
                }
                // Convert accumulated days to months if possible
                if (dayst >= daysInMonth(m, y)) {
                    months += 1;
                    dayst -= daysInMonth(m, y);
                }
            }
            // Convert months to years if possible
            if (months >= 12) {
                years += months / 12;
                months = months % 12;
            }
        }
    }
  
    void display() {
        cout << "\n\n-----Output-----\n\n";
        if (days<=0) { days=0; dayst=0; }
        // resolves the days lived to zero if today's date is less than the date of birth
        cout << "Number of days lived : " << days;
        cout << endl;
        if(!(days<=0))
        {
        if (years) cout << years << " years ";
        if (months) cout << months << " months ";
        if (dayst) cout << dayst << " days ";
        if (years && months && dayst) cout << "old" << endl;
        }
    }
};

int main() {
    cout << "-----Age Calculation Program-----" <<endl;
    DateInput o1; // Date of birth
    DateInput o2; // Current date
    cout << "Enter the date of birth [DD/MM/YYYY] :" << endl;
    o1.input();
    o1.convert();
    cout << "Enter today's date [DD/MM/YYYY] :" << endl;
    o2.input();
    o2.convert();
    
    DateCalculation o3;
    o3.calculate(o1, o2);

    cout << "Inputs : -" <<endl;
    cout << "Date of birth : " << o1.day << "/" << o1.month << "/" << o1.year  <<endl;
    cout << "Today's date : " << o2.day << "/" << o2.month << "/" << o2.year   <<endl;
    o3.display();
    
    return 0;
}

#include "Date.h"

Date::Date(){day=month=year=0;}
void Date::setDay(int d){day=d;}
void Date::setMonth(int m){month=m;}
void Date::setYear(int y){year=y;}
int Date::getDay(){return day;}
int Date::getMonth(){return month;}
int Date::getYear(){return year;}
bool Date::isLeapYear(int temp){
    if(temp%4!=0)
        return false;
    else if(temp%100==0)
        return temp%400==0;
    return true;
}
bool Date::leapYear(){
    int temp=year;
    return isLeapYear(temp);
}
bool Date::setDate(int D,int M, int Y){//Can't be before or at 31/12/1899
    if(Y<1900 || D<1 || M<1)//floors
        return false;
    if(!isLeapYear(Y) && (M==2 && D>28))//If not a leap year then February's ceiling is 28 days
        return false;
    if(isLeapYear(Y) && (M==2 && D>29))//If it is then it's 29 days
        return false;
    if((M==1 || M==3 || M==5 || M==7 || M==8 || M==10 || M==12) && D>31)//Months listed are the 31d ones
        return false;
    if ((M==4 || M==6 || M==9 || M==11) && D>30)//February already checked
        return false;
    day=D;
    month=M;
    year=Y;
    return true;
}
void Date::dayOfWeek(int &rank_of_day){//Sakamoto's method
    int tmp_day,tmp_month,tmp_year;
    tmp_day=day;
    tmp_month=month;
    tmp_year=year;
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if(tmp_month<3)
        tmp_year--;
    rank_of_day=(tmp_year + tmp_year/4 - tmp_year/100 + tmp_year/400 + t[tmp_month-1] + tmp_day) % 7;
}
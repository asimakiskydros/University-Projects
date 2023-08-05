#include "Date.h"

Date::Date(){day=month=year=0;}
Date::Date(int d,int m, int y){
    day=d;
    month=m;
    year=y;
}
void Date::set_day(int num){day=num;}
void Date::set_month(int num){month=num;}
void Date::set_year(int num){year=num;}
int Date::get_day(){return day;}
int Date::get_month(){return month;}
int Date::get_year(){return year;}
int Date::daysInMonth(int m){
    if(m<1 || m>12)
        return -1;
    if(m==2)
        return 28;
    if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
        return 31;
    else
        return 30;
}
void Date::add(int k){
    int rmndr=0;
    day+=k;
    if((rmndr=day-daysInMonth(month))>0){
        day=rmndr;
        month++;
        if(month>12){
            month=1;
            year++;
        }
    }
}
long Date::diff(Date &other){
    long days_this=day,days_other=other.day;
    int i;
    for(i=month-1;i>0;i--)
        days_this+=daysInMonth(i);
    for(i=other.month-1;i>0;i--)
        days_other+=daysInMonth(i);
    days_this+=365*(year-1);
    days_other+=365*(other.year-1);
    return days_other-days_this;
}
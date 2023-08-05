#ifndef Date_h
#define Date_h
class Date{
    private:
        int day,month,year;
        bool isLeapYear(int);
    public:
        Date();
        bool setDate(int,int,int);
        void dayOfWeek(int&);
        void setDay(int);
        void setMonth(int);
        void setYear(int);
        int getDay();
        int getMonth();
        int getYear();
        bool leapYear();
};
#endif
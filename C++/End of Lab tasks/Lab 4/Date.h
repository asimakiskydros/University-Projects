#ifndef DATE_H
#define DATE_H
class Date{
    private:
        int day,month,year;
    public:
        Date();
        Date(int,int,int);
        void set_day(int);
        void set_month(int);
        void set_year(int);
        int get_day();
        int get_month();
        int get_year();
        int daysInMonth(int);
        void add(int);
        long diff(Date &);
};
#endif //DATE_H
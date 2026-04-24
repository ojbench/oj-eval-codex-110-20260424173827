// Implement Date operations per problem spec
#include <iostream>
using namespace std;

static const int month_days_common[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Date {
    int _year;
    int _month;
    int _day;

    Date(): _year(1900), _month(1), _day(1) {}
    Date(int y, int m, int d) {
        if (is_valid(y, m, d)) { _year=y; _month=m; _day=d; }
        else { _year=1900; _month=1; _day=1; }
    }

    static bool is_leap(int y){
        return (y%4==0 && y%100!=0) || (y%400==0);
    }

    static bool is_valid(int y,int m,int d){
        if (y<1900 || y>2030) return false;
        if (m<1 || m>12) return false;
        int md = month_days_common[m] + (m==2 && is_leap(y) ? 1:0);
        if (d<1 || d>md) return false;
        return true;
    }

    // helpers: convert to days since 1900-01-01 and back
    static long long to_serial(int y,int m,int d){
        long long days=0;
        for(int yy=1900; yy<y; ++yy){
            days += is_leap(yy)?366:365;
        }
        for(int mm=1; mm<m; ++mm){
            days += month_days_common[mm];
            if(mm==2 && is_leap(y)) days += 1;
        }
        days += (d-1); // 1900-01-01 -> 0
        return days;
    }

    static void from_serial(long long s, int &y,int &m,int &d){
        y = 1900;
        // support negative serials by moving to previous years
        while(s < 0){
            int py = y - 1;
            long long year_days_prev = is_leap(py)?366:365;
            s += year_days_prev;
            y = py;
        }
        while(true){
            long long year_days = is_leap(y)?366:365;
            if(s >= year_days){ s -= year_days; ++y; }
            else break;
        }
        m = 1;
        while(true){
            int md = month_days_common[m] + (m==2 && is_leap(y) ? 1:0);
            if(s >= md){ s -= md; ++m; }
            else break;
        }
        d = (int)s + 1;
    }

    // ++/-- and +/- days
    Date& operator++(){ // prefix
        long long s = to_serial(_year,_month,_day);
        from_serial(s+1, _year,_month,_day);
        return *this;
    }
    Date operator++(int){ // postfix
        Date old = *this;
        ++(*this);
        return old;
    }
    Date& operator--(){ // prefix
        long long s = to_serial(_year,_month,_day);
        from_serial(s-1, _year,_month,_day);
        return *this;
    }
    Date operator--(int){ // postfix
        Date old = *this;
        --(*this);
        return old;
    }

    Date operator+(long long days) const{
        long long s = to_serial(_year,_month,_day);
        Date r; from_serial(s+days, r._year,r._month,r._day);
        return r;
    }
    Date operator-(long long days) const{
        long long s = to_serial(_year,_month,_day);
        Date r; from_serial(s-days, r._year,r._month,r._day);
        return r;
    }

    long long operator-(const Date& other) const{
        long long a = to_serial(_year,_month,_day);
        long long b = to_serial(other._year,other._month,other._day);
        long long diff = a-b; if(diff<0) diff = -diff; return diff;
    }

    bool operator<(const Date& other) const{
        if(_year!=other._year) return _year<other._year;
        if(_month!=other._month) return _month<other._month;
        return _day<other._day;
    }
};

ostream& operator<<(ostream& os, const Date& d){
    os << d._year << '-' << d._month << '-' << d._day;
    return os;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op; if(!(cin>>op)) return 0;
    int yy, mm, dd;

    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << '\n';
        cout << d1 << '\n';
        cout << d2 << '\n';
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << '\n';
        for (int i=0;i<5;++i) cout << d0++ << '\n';
        for (int i=0;i<5;++i) cout << d0-- << '\n';
        for (int i=0;i<2;++i) cout << --d0 << '\n';
        cout << d0 << '\n';
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << '\n';
        cout << d0 - 1000 << '\n';
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << '\n';
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << '\n';
    }
    return 0;
}

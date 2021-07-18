#ifndef DATE_H
#define DATE_H

#define _CRT_SECURE_NO_WARNINGS



#include <iosfwd>
#include <ctime>
#include <unordered_map>
#include <string>


class Date {
public:
	static constexpr int year_base = 1900;  //1
	static constexpr int random_min_year = 1940;  //2
	static constexpr int random_max_year = 2020;  //3
	enum class WeekDay { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4
	Date(); //5 
	Date(int d, int m, int y);  //6
	Date(const char* p);  //7
	Date(std::time_t timer); //8
	int get_month_day()const { return m_day; } //9
	int get_month()const { return m_month; } //10
	int get_year()const { return m_year; } //11
	int get_year_day()const; //12
	int days_since_1900()const;
	WeekDay get_week_day()const; //13

	Date& set_month_day(int day) { m_day = day; return *this; } //14
	Date& set_month(int month) { m_month = month; return *this; } //15
	Date& set_year(int year) { m_year = year; return *this; } //16

	Date(const Date&) = default;
	Date& operator=(const Date&);

	
	Date operator-(int day)const; //17
	Date& operator+=(int day); //18
	Date& operator-=(int day); //19
	Date& operator++() { return *this += 1; } //20
	Date operator++(int); //21
	Date& operator--() { return *this -= 1; } //22
	Date operator--(int); //23

	const char* print_weekday()const;
	static Date random_date(); //24
	static constexpr bool isleap(int y); //25

private:
	int m_day, m_month, m_year;

	Date year_day_to_date(int year_day, const int year)const;

	const enum class months {January, February, March,	April, May, June,
			July, August, September, October, November,	December};

	const uint8_t days_of_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	const uint8_t days_of_months_leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
};

bool operator<(const Date&, const Date&); //26
inline bool operator<=(const Date& dt1, const Date& dt2) 
{ return !(dt2 < dt1); } //27
inline bool operator>(const Date& dt1, const Date& dt2)
{ return dt2 < dt1; }//28
inline bool operator>=(const Date& dt1, const Date& dt2) 
{ return !(dt1 < dt2); } //29
bool operator==(const Date&, const Date&); //30
inline bool operator!=(const Date& dt1, const Date& dt2) 
{ return !(dt1 == dt2); } //31

int operator-(const Date& d1, const Date& d2); //32
Date operator+(const Date& date, int n); //33
Date operator+(int n, const Date&); //34
Date::WeekDay& operator++(Date::WeekDay& r); //35
Date::WeekDay operator++(Date::WeekDay& r, int); //36
Date::WeekDay& operator--(Date::WeekDay& r); //37
Date::WeekDay operator--(Date::WeekDay& r, int); //38

std::ostream& operator<<(std::ostream& os, const Date& date); //39
std::istream& operator>>(std::istream& is, Date& date); //40

#endif // !DATE_H


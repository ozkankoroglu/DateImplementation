#pragma once
#include <ctime>
#include <iostream>
#include "date.h"



inline void check_day_of_year()
{
	// this function will print which day of the year today is
	// to validate : https://www.epochconverter.com/days
	std::time_t  timer = time(NULL);
	Date mydate1{ timer };
	std::cout << "today is = " << mydate1.get_year_day() << "th day of this year"<< "\n";
}

inline void check_week_day()
{
	// this function will print which day of the week today is
	
	std::time_t  timer;
	time(&timer);
	Date mydate{ timer };
	switch (mydate.get_week_day())
	{
	case Date::WeekDay::Sunday: std::cout << "today is Sunday" << "\n"; break;
	case Date::WeekDay::Monday: std::cout << "today is Monday" << "\n"; break;
	case Date::WeekDay::Tuesday: std::cout << "today is Tuesday" << "\n"; break;
	case Date::WeekDay::Wednesday: std::cout << "today is Wednesday" << "\n"; break;
	case Date::WeekDay::Thursday: std::cout << "today is Thursday" << "\n"; break;
	case Date::WeekDay::Friday: std::cout << "today is Friday" << "\n"; break;
	case Date::WeekDay::Saturday: std::cout << "today is Saturday" << "\n"; break;
	}
	
}

inline void test_set_and_get_functions()
{
	Date date;
	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";

	date.set_month_day(21);
	date.set_month(3);
	date.set_year(1996);

	std::cout << "-------------------------------------------\n";

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";
}


inline void test_minus_operator()
{
	Date date{21,3,1996};

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";

	Date new_date = date - 365;

	std::cout << "-------------------------------------------\n";

	std::cout << "month day = " << new_date.get_month_day() << "\n";
	std::cout << "month = " << new_date.get_month() << "\n";
	std::cout << "year = " << new_date.get_year() << "\n";
}

inline void test_addition_assignment_operator()
{
	Date date{ 22,3,1995 };

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";

	date += 365;

	std::cout << "-------------------------------------------\n";

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";
}

inline void test_subtraction_assignment_operator()
{
	Date date{ 21,3,1996 };

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";

	date -= 365;

	std::cout << "-------------------------------------------\n";

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";
}

inline void test_plusplus_minusminus_operators()
{
	Date date{ 21,3,1996 };

	std::cout << "month day = " << date.get_month_day() << "\n";
	std::cout << "month = " << date.get_month() << "\n";
	std::cout << "year = " << date.get_year() << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "(++date).get_month_day() = " << (++date).get_month_day() << "\n";
	std::cout << "(date++).get_month_day() = " << (date++).get_month_day() << "\n";
	std::cout << "date.get_month_day() = " << date.get_month_day() << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "(--date).get_month_day() = " << (--date).get_month_day() << "\n";
	std::cout << "(date--).get_month_day() = " << (date--).get_month_day() << "\n";
	std::cout << "date.get_month_day() = " << date.get_month_day() << "\n";

}

inline void test_random_date_generator()
{
	for(int i = 0; i < 100; i++)
	{
		Date date = Date::random_date();

		std::cout << date.get_month_day() << "-" << date.get_month()
			<< "-" << date.get_year() << "\n";
		std::cout << "-------------------------------------------\n";
	}
}

inline void test_date_minus_date()
{
	Date d1 = Date::random_date();
	std::cout << d1.get_month_day() << "-" <<
		d1.get_month() << "-" << d1.get_year() << "\n";

	Date d2 = Date::random_date();
	std::cout << d2.get_month_day() << "-" <<
		d2.get_month() << "-" << d2.get_year() << "\n";

	std::cout << "day difference d1-d2 = " << (d1 - d2) << "\n";
}

inline void test_weekday_operator_pluspus()
{
	Date::WeekDay Wd = Date::WeekDay::Monday;

	std::cout << "Weekday : " << static_cast<int>(Wd) << "\n";

	(++Wd)++;

	std::cout << "Weekday : " << static_cast<int>(Wd) << "\n";
}

inline void test_weekday_operator_minusminus()
{
	Date::WeekDay Wd = Date::WeekDay::Monday;

	std::cout << "Weekday : " << static_cast<int>(Wd) << "\n";

	(--Wd)--;

	std::cout << "Weekday : " << static_cast<int>(Wd) << "\n";
}

inline void test_date_ostream()
{
	Date d{ 21,3,1996 };

	std::cout << d;
}


inline void test_date_istream()
{
	Date d;

	std::cin >> d;

	std::cout << d;
}
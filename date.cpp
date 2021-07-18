#include "date.h"
#include <iostream>
#include <string>



Date::Date() : m_day{1}, m_month{1}, m_year{1900}
{
	//std::cout << "default ctor called\n";
}

Date::Date(int d, int m, int y): m_day{ d }, m_month{ m }, m_year{ y }
{
	//std::cout << "ctor called with : d = " << m_day
	//									   << ", m = " << m_month
	//									   << ", y = " << m_year << "\n";
}

Date::Date(const char* p)
{
	size_t idx = 0;
	m_day = std::stoi(p, &idx);
	size_t idx_month = idx + 1;
	m_month = std::stoi(p + idx_month , &idx);
	size_t idx_year = idx_month + idx + 1;
	m_year = std::stoi(p + idx_year);

	//std::cout << "ctor called with : d = " << m_day
	//	<< ", m = " << m_month
	//	<< ", y = " << m_year << "\n";
}

Date::Date(std::time_t timer)
{
	tm* ptr = std::gmtime(&timer);
	m_day = ptr->tm_mday;
	m_month = ptr->tm_mon + 1;
	m_year = ptr->tm_year + 1900;


	//std::cout << "ctor called with : d = " << m_day
	//	<< ", m = " << m_month
	//	<< ", y = " << m_year << "\n";
}

int Date::get_year_day()const
{
	tm date{};
	date.tm_year = m_year - 1900;
	date.tm_mon = m_month - 1;
	date.tm_mday = m_day + 1;
	mktime(&date);
	return date.tm_yday;
}

Date::WeekDay Date::get_week_day()const
{
	tm date{};
	date.tm_year = m_year - 1900;
	date.tm_mon = m_month - 1;
	date.tm_mday = m_day;
	mktime(&date);
	return static_cast<WeekDay>(date.tm_wday);
}

Date& Date::operator=(const Date& other)
{
	if (this == &other)
		return *this;

	m_day = other.m_day;
	m_month = other.m_month;
	m_year = other.m_year;

	return *this;
}

Date Date::operator-(int day) const
{
	auto&& r = Date{m_day, m_month, m_year};
	int year_day = r.get_year_day();
	year_day -= day;

	while (year_day < 1)
	{
		if (isleap(r.m_year - 1))
		{
			year_day += 366;
		}
		else
		{
			year_day += 365;
		}
		--r.m_year;
	}

	return year_day_to_date(year_day, r.m_year);;
}

Date& Date::operator+=(int day)
{
	int year_day = get_year_day();
	year_day += day;
	
	while (year_day > 365)
	{
		if (!isleap(m_year))
		{
			year_day -= 365;
			m_year++;
		}
		else if (year_day > 366)
		{
			year_day -= 366;
			m_year++;
		}
	}

	return *this = year_day_to_date(year_day, m_year);
}

Date& Date::operator-=(int day)
{
	int year_day = get_year_day();
	year_day -= day;

	while (year_day < 1)
	{
		if (isleap(m_year - 1))
		{
			year_day += 366;
		}
		else
		{
			year_day += 365;
		}
		--m_year;
	}

	return *this = year_day_to_date(year_day, m_year);
}

Date Date::operator++(int)
{
	Date temp_date = *this;
	*this += 1;
	return temp_date;
}

Date Date::operator--(int)
{
	Date temp_date = *this;
	*this -= 1;
	return temp_date;
}

Date::WeekDay& operator++(Date::WeekDay& r) 
{
	switch (r)
	{
	case Date::WeekDay::Monday: r = Date::WeekDay::Tuesday; break;
	case Date::WeekDay::Tuesday: r = Date::WeekDay::Wednesday; break;
	case Date::WeekDay::Wednesday: r = Date::WeekDay::Thursday; break;
	case Date::WeekDay::Thursday: r = Date::WeekDay::Friday; break;
	case Date::WeekDay::Friday: r = Date::WeekDay::Saturday; break;
	case Date::WeekDay::Saturday: r = Date::WeekDay::Sunday; break;
	case Date::WeekDay::Sunday: r = Date::WeekDay::Monday; break;
	}
	return r;
}

Date::WeekDay operator++(Date::WeekDay& r, int)
{
	auto&& ref = r;
	++ref;
	return ref;
}

Date::WeekDay& operator--(Date::WeekDay& r)
{
	switch (r)
	{
	case Date::WeekDay::Monday: r = Date::WeekDay::Sunday; break;
	case Date::WeekDay::Tuesday: r = Date::WeekDay::Monday; break;
	case Date::WeekDay::Wednesday: r = Date::WeekDay::Tuesday; break;
	case Date::WeekDay::Thursday: r = Date::WeekDay::Wednesday; break;
	case Date::WeekDay::Friday: r = Date::WeekDay::Thursday; break;
	case Date::WeekDay::Saturday: r = Date::WeekDay::Friday; break;
	case Date::WeekDay::Sunday: r = Date::WeekDay::Saturday; break;
	}
	return r;
}

Date::WeekDay operator--(Date::WeekDay& r, int)
{
	auto&& ref = r;
	--ref;
	return ref;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.get_month_day() << "-" << date.get_month() << "-" << date.get_year() <<
		"-" << date.print_weekday() << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
	int day, month, year;
	std::cout << "Gun: ";
	is >> day;
	std::cout << "Ay: ";
	is >> month;
	std::cout << "Yil: ";
	is >> year;

	date.set_month_day(day);
	date.set_month(month);
	date.set_year(year);

	return is;
}

Date Date::random_date()
{
	auto&& r = Date{};
	static bool randomized = false;
	if (!randomized)
	{
		srand(time(NULL));
		randomized = true;
	}
	r.m_year = (rand() % 150) + 1900;
	r.m_month = (rand() % 12) + 1;
	int day = 0;
	if (r.m_month == 2)
	{
		day = isleap(r.m_year) ? ((rand() % 29) + 1) : ((rand() % 28) + 1);
	}
	else
	{
		day = (rand() % r.days_of_months[r.m_month - 1]) + 1;
	}
	r.m_day = day;

	return r;
}

bool operator<(const Date& dt1, const Date& dt2)
{
	if (dt1.get_year() < dt2.get_year()) return true;
	else if (dt1.get_year() > dt2.get_year()) return false;
	else
	{
		if (dt1.get_month() < dt2.get_month()) return true;
		else if (dt1.get_month() > dt2.get_month()) return false;
		else
		{
			if (dt1.get_month_day() < dt2.get_month_day()) return true;
			else 
				return false;
		}
	}
}

bool operator==(const Date& dt1, const Date& dt2)
{
	if ((dt1.get_month_day() == dt2.get_month_day()) &&
		(dt1.get_month() == dt2.get_month()) &&
		(dt1.get_year() == dt2.get_year())) return true;

	return false;
}

int operator-(const Date& d1, const Date& d2)
{
	int days = d1.days_since_1900() - d2.days_since_1900();
	return abs(days);
}

Date operator+(const Date& date, int n)
{
	Date temp_date = date;
	temp_date += n;
	return temp_date;
}

Date operator+(int n, const Date& date)
{
	return (date + n);
}

Date Date::year_day_to_date(int year_day, const int year)const
{
	Date mydate{ 1, 1, year };
	int temp_month = 1;
	if (isleap(year))
	{
		//std::cout << year << " is a leap year.\n";
		for (int i = 0; year_day > days_of_months_leap[i]; i++)
		{
			year_day -= days_of_months_leap[i];
			temp_month++;
		}
	}
	else
	{
		for (int i = 0; year_day > days_of_months[i]; i++)
		{
			year_day -= days_of_months[i];
			temp_month++;
		}
	}
	//std::cout << "year_day = " << year_day << ", temp_month = " << temp_month << "\n";

	mydate.set_month_day(year_day);
	mydate.set_month(temp_month);

	return mydate;
}

int Date::days_since_1900()const
{
	int days = this->get_year_day();
	int year = this->get_year();

	while (year-- > 1900)
	{
		days += isleap(year) ? 366 : 365;
	}

	return days;
}

bool constexpr Date::isleap(int y)
{
	if (y % 4 == 0) 
	{
		if (y % 100 == 0) 
		{
			if (y % 400 == 0) 
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

const char* Date::print_weekday()const
{
	Date::WeekDay Wd = this->get_week_day();
	switch (Wd)
	{
	case Date::WeekDay::Sunday: return "Sunday";
	case Date::WeekDay::Monday: return "Monday";
	case Date::WeekDay::Tuesday: return "Tuesday";
	case Date::WeekDay::Wednesday: return "Wednesday";
	case Date::WeekDay::Thursday: return "Thursday";
	case Date::WeekDay::Friday: return "Friday";
	case Date::WeekDay::Saturday: return "Saturday";
	}
	
}
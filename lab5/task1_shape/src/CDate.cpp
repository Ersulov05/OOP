#include "./CDate.h"
#include "./Exception/DateOutOfRangeException.h"
#include "./Exception/DayOutOfRangeMonthException.h"
#include <cmath>
#include <iomanip>

CDate& CDate::operator=(const CDate& other)
{
	if (this != &other)
	{
		m_timestamp = other.m_timestamp;
	}
	return *this;
}

CDate& CDate::operator++()
{
	AddDays(1);
	return *this;
}

CDate& CDate::operator--()
{
	SubDays(1);
	return *this;
}

CDate CDate::operator++(int)
{
	CDate copy = *this;
	AddDays(1);
	return copy;
}

CDate CDate::operator--(int)
{
	CDate copy = *this;
	SubDays(1);
	return copy;
}

CDate CDate::operator+(int days)
{
	CDate copy = *this;
	copy.AddDays(days);
	return copy;
}

CDate operator+(int days, const CDate& date)
{
	CDate copy = date;
	copy.AddDays(days);
	return copy;
}

CDate CDate::operator-(int days)
{
	CDate copy = *this;
	copy.SubDays(days);
	return copy;
}

int operator-(const CDate& firstDate, const CDate& secondDate)
{
	return (int)firstDate.m_timestamp - (int)secondDate.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
	AddDays(days);
	return *this;
}

CDate& CDate::operator-=(int days)
{
	SubDays(days);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << std::setw(2) << std::setfill('0') << static_cast<unsigned>(date.GetMonth()) << CDate::DATE_SEPARATOR
	   << std::setw(2) << std::setfill('0') << date.GetDay() << CDate::DATE_SEPARATOR
	   << std::setw(4) << std::setfill('0') << date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned year, month, day;
	char sep1, sep2;

	if (is >> day >> sep1 >> month >> sep2 >> year)
	{
		if (sep1 == CDate::DATE_SEPARATOR && sep2 == CDate::DATE_SEPARATOR && CDate::IsValidDate(day, month, year))
		{
			date = CDate(day, static_cast<Month>(month), year);
			return is;
		}
	}

	is.setstate(std::ios::failbit);
	return is;
}

bool operator==(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp == secondDate.m_timestamp;
}

bool operator!=(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp != secondDate.m_timestamp;
}

bool operator>(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp > secondDate.m_timestamp;
}

bool operator<(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp < secondDate.m_timestamp;
}

bool operator>=(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp >= secondDate.m_timestamp;
}

bool operator<=(const CDate& firsDate, const CDate& secondDate)
{
	return firsDate.m_timestamp <= secondDate.m_timestamp;
}

CDate::CDate(unsigned day, Month month, unsigned year)
	: m_timestamp(ConvertDateToTimestamp(day, month, year))
{
	AssertValidDate(day, month, year);
}

CDate::CDate(unsigned timestamp)
	: m_timestamp(timestamp)
{
	AssertValidTimestamp(timestamp);
}

CDate::CDate()
	: m_timestamp(0)
{
}

unsigned CDate::GetDay() const
{
	unsigned year = GetYear();
	Month month = GetMonth();
	unsigned daysBeforeMonth = GetDaysBeforeMonth(month, year);

	return m_timestamp - (GetCountDaysBeforeYear(GetYear()) + daysBeforeMonth - NUMBER_DAYS_BEFORE_START_YEAR) + 1;
}

Month CDate::GetMonth() const
{
	unsigned year = GetYear();
	unsigned days = m_timestamp - (GetCountDaysBeforeYear(year) - NUMBER_DAYS_BEFORE_START_YEAR);

	int intMonth = std::min((days / DAYS_PER_MONTH + 1), MONTH_PER_YEAR);
	Month month = static_cast<Month>(intMonth);

	unsigned minDayMonth = GetDaysBeforeMonth(month, year);
	if (days < minDayMonth)
		return static_cast<Month>(intMonth - 1);

	unsigned maxDayMonth = minDayMonth + GetDaysInMonth(month, year);
	if (days > maxDayMonth)
		return static_cast<Month>(intMonth + 1);

	return month;
}

// возвращает год
// t = y * 365 + y/4 - y/100 + y/400
// y = 400 * t / (365 * 400 + 100 + 4 + 1)
unsigned CDate::GetYear() const
{
	return 400 * (m_timestamp + NUMBER_DAYS_BEFORE_START_YEAR + 1) / (DAYS_PER_YEAR * 400 + 100 - 4 + 1);
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + static_cast<unsigned>(WeekDay::THURSDAY)) % DAYS_PER_WEEK);
}

void CDate::AssertValidDate(unsigned day, Month month, unsigned year) const
{
	if (year < START_YEAR || year > MAX_YEAR)
	{
		throw DateOutOfRangeException();
	}

	if (day > GetDaysInMonth(month, year) || day < 1)
	{
		throw DayOutOfRangeMonthException();
	}
}

bool CDate::IsValidDate(unsigned day, unsigned month, unsigned year)
{
	if (year < START_YEAR || year > MAX_YEAR || month < MIN_MONTH || month > MAX_MONTH)
	{
		return false;
	}

	if (day > GetDaysInMonth(static_cast<Month>(month), year) || day < 1)
	{
		return false;
	}

	return true;
}

void CDate::AssertValidTimestamp(unsigned timestamp) const
{
	if (timestamp > MAX_TIMESTAMP)
	{
		throw DateOutOfRangeException();
	}
}

unsigned CDate::GetCountLeapYears(unsigned year) const
{
	return year / 4 - year / 100 + year / 400;
}

unsigned CDate::GetCountDaysBeforeYear(unsigned year) const
{
	return year * DAYS_PER_YEAR + GetCountLeapYears(year);
}

unsigned CDate::GetDaysInMonth(Month month, unsigned year)
{
	return IsLeapYear(year) && month == Month::FEBRUARY
		? DAYS_PER_MONTH_MAP.at(month) + 1
		: DAYS_PER_MONTH_MAP.at(month);
}

unsigned CDate::GetDaysBeforeMonth(Month month, unsigned year) const
{
	return IsLeapYear(year) && month > Month::FEBRUARY
		? SUMM_DAYS_IN_MONTHS_MAP.at(month) + 1
		: SUMM_DAYS_IN_MONTHS_MAP.at(month);
}

unsigned CDate::GetCountDaysBeforeDate(unsigned day, Month month, unsigned year) const
{
	return day + GetDaysBeforeMonth(month, year) + GetCountDaysBeforeYear(year) - 1;
}

unsigned CDate::IsLeapYear(unsigned year)
{
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

unsigned CDate::ConvertDateToTimestamp(unsigned day, Month month, unsigned year) const
{
	return GetCountDaysBeforeDate(day, month, year) - NUMBER_DAYS_BEFORE_START_YEAR;
}

void CDate::AssertValidAddition(unsigned delta) const
{
	if (delta > MAX_TIMESTAMP - m_timestamp)
	{
		throw DateOutOfRangeException();
	}
}

void CDate::AssertValidSubstraction(unsigned delta) const
{
	if (delta > m_timestamp)
	{
		throw DateOutOfRangeException();
	}
}

void CDate::AddDays(unsigned days)
{
	AssertValidAddition(days);
	m_timestamp += days;
}

void CDate::SubDays(unsigned days)
{
	AssertValidSubstraction(days);
	m_timestamp -= days;
}
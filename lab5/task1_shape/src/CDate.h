#include <iostream>
#include <map>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CDate
{
public:
	CDate& operator++();
	CDate& operator--();
	CDate operator++(int);
	CDate operator--(int);
	CDate operator+(int);
	friend CDate operator+(int days, CDate date);
	CDate operator-(int);
	friend int operator-(CDate firstDate, CDate secondDate);
	CDate& operator+=(int);
	CDate& operator-=(int);
	friend std::ostream& operator<<(std::ostream& os, const CDate& date);
	friend std::istream& operator>>(std::istream& is, CDate& date);
	friend bool operator==(const CDate& firsDate, const CDate& secondDate);
	friend bool operator!=(const CDate& firsDate, const CDate& secondDate);
	friend bool operator>(const CDate& firsDate, const CDate& secondDate);
	friend bool operator<(const CDate& firsDate, const CDate& secondDate);
	friend bool operator>=(const CDate& firsDate, const CDate& secondDate);
	friend bool operator<=(const CDate& firsDate, const CDate& secondDate);
	CDate& operator=(const CDate& other);

	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timestamp);
	CDate();
	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	inline static const char DATE_SEPARATOR = '-';
	static bool IsValidDate(unsigned day, unsigned month, unsigned year);

private:
	inline static const std::map<Month, unsigned> DAYS_PER_MONTH_MAP = {
		{ Month::JANUARY, 31 },
		{ Month::FEBRUARY, 28 },
		{ Month::MARCH, 31 },
		{ Month::APRIL, 30 },
		{ Month::MAY, 31 },
		{ Month::JUNE, 30 },
		{ Month::JULY, 31 },
		{ Month::AUGUST, 31 },
		{ Month::SEPTEMBER, 30 },
		{ Month::OCTOBER, 31 },
		{ Month::NOVEMBER, 30 },
		{ Month::DECEMBER, 31 }
	};
	inline static const std::map<Month, unsigned> SUMM_DAYS_IN_MONTHS_MAP = {
		{ Month::JANUARY, 0 },
		{ Month::FEBRUARY, 31 },
		{ Month::MARCH, 59 },
		{ Month::APRIL, 90 },
		{ Month::MAY, 120 },
		{ Month::JUNE, 151 },
		{ Month::JULY, 181 },
		{ Month::AUGUST, 212 },
		{ Month::SEPTEMBER, 243 },
		{ Month::OCTOBER, 273 },
		{ Month::NOVEMBER, 304 },
		{ Month::DECEMBER, 334 }
	};

	void AssertValidDate(unsigned day, Month month, unsigned year) const;
	void AssertValidTimestamp(unsigned timestamp) const;
	unsigned GetCountLeapYears(unsigned year) const;

	unsigned GetCountDaysBeforeDate(unsigned day, Month month, unsigned year) const;
	unsigned ConvertDateToTimestamp(unsigned day, Month month, unsigned year) const;
	static unsigned IsLeapYear(unsigned year);
	static unsigned GetDaysInMonth(Month month, unsigned year);
	unsigned GetDaysBeforeMonth(Month month, unsigned year) const;
	unsigned GetCountDaysBeforeYear(unsigned year) const;

	void AssertValidAddition(unsigned delta);
	void AssertValidSubstraction(unsigned delta);

	static const unsigned START_YEAR = 1970;
	static const unsigned MAX_YEAR = 9999;
	static const unsigned MIN_MONTH = 1;
	static const unsigned MAX_MONTH = 12;
	const unsigned DAYS_PER_YEAR = 365;
	const unsigned MONTH_PER_YEAR = 12;
	const unsigned DAYS_PER_MONTH = 30;
	const unsigned NUMBER_DAYS_BEFORE_START_YEAR = GetCountDaysBeforeYear(START_YEAR);
	const unsigned NUMBER_OF_LEAP_YEARS_BEFORE_START_YEAR = GetCountLeapYears(START_YEAR);
	const unsigned MAX_TIMESTAMP = GetCountDaysBeforeDate(31, Month::DECEMBER, MAX_YEAR) - NUMBER_DAYS_BEFORE_START_YEAR;

	unsigned m_timestamp;
};
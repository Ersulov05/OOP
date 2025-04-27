#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CDate.h"
#include "../src/Exception/DateOutOfRangeException.h"
#include "../src/Exception/DayOutOfRangeMonthException.h"
#include <sstream>

TEST_CASE("TestCreateDateSuccess")
{
	CDate date;

	date = CDate(2, Month::JANUARY, 1970);
	REQUIRE(date.GetDay() == 2);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);

	date = CDate(9, Month::JUNE, 2005);
	REQUIRE(date.GetDay() == 9);
	REQUIRE(date.GetMonth() == Month::JUNE);
	REQUIRE(date.GetYear() == 2005);
	REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);

	date = CDate();
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("TestCreateDateAllMonthSuccess")
{
	CDate date;

	date = CDate(20);
	REQUIRE(date.GetDay() == 21);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);

	date = CDate(40);
	REQUIRE(date.GetDay() == 10);
	REQUIRE(date.GetMonth() == Month::FEBRUARY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);

	date = CDate(60);
	REQUIRE(date.GetDay() == 2);
	REQUIRE(date.GetMonth() == Month::MARCH);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);

	date = CDate(90);
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::APRIL);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);

	date = CDate(140);
	REQUIRE(date.GetDay() == 21);
	REQUIRE(date.GetMonth() == Month::MAY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);

	date = CDate(160);
	REQUIRE(date.GetDay() == 10);
	REQUIRE(date.GetMonth() == Month::JUNE);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);

	date = CDate(211);
	REQUIRE(date.GetDay() == 31);
	REQUIRE(date.GetMonth() == Month::JULY);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);

	date = CDate(240);
	REQUIRE(date.GetDay() == 29);
	REQUIRE(date.GetMonth() == Month::AUGUST);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);

	date = CDate(260);
	REQUIRE(date.GetDay() == 18);
	REQUIRE(date.GetMonth() == Month::SEPTEMBER);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);

	date = CDate(280);
	REQUIRE(date.GetDay() == 8);
	REQUIRE(date.GetMonth() == Month::OCTOBER);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);

	date = CDate(310);
	REQUIRE(date.GetDay() == 7);
	REQUIRE(date.GetMonth() == Month::NOVEMBER);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);

	date = CDate(340);
	REQUIRE(date.GetDay() == 7);
	REQUIRE(date.GetMonth() == Month::DECEMBER);
	REQUIRE(date.GetYear() == 1970);
	REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);

	date = CDate(365);
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 1971);
	REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
}

TEST_CASE("TestCreateDateAllWeekDaysSuccess")
{
	CDate date;

	date = CDate(3);
	REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);

	date = CDate(4);
	REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);

	date = CDate(5);
	REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);

	date = CDate(6);
	REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);

	date = CDate(7);
	REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);

	date = CDate(8);
	REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);

	date = CDate(9);
	REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);

	date = CDate(10);
	REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);
}

TEST_CASE("TestCreateDateYearOutOfRangeFailed")
{
	REQUIRE_THROWS_AS(CDate(1, Month::JANUARY, 1900), DateOutOfRangeException);
	REQUIRE_THROWS_AS(CDate(1, Month::JANUARY, 0), DateOutOfRangeException);
	REQUIRE_THROWS_AS(CDate(1, Month::JANUARY, 1969), DateOutOfRangeException);
}

TEST_CASE("TestCreateDateDayOutOfRangeMonthFailed")
{
	REQUIRE_THROWS_AS(CDate(0, Month::JANUARY, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::JANUARY, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(29, Month::FEBRUARY, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(30, Month::FEBRUARY, 1972), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::MARCH, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(31, Month::APRIL, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::MAY, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(31, Month::JUNE, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::JULY, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::AUGUST, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(31, Month::SEPTEMBER, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::OCTOBER, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(31, Month::NOVEMBER, 1970), DayOutOfRangeMonthException);
	REQUIRE_THROWS_AS(CDate(32, Month::DECEMBER, 1970), DayOutOfRangeMonthException);
}

TEST_CASE("TestDatePlusMinusOperationsSuccess")
{
	CDate date;
	CDate secondDate;
	REQUIRE(date.GetDay() == 1);

	secondDate = date++;
	REQUIRE(secondDate.GetDay() == 1);
	REQUIRE(date.GetDay() == 2);

	secondDate = date--;
	REQUIRE(secondDate.GetDay() == 2);
	REQUIRE(date.GetDay() == 1);

	secondDate = ++date;
	REQUIRE(secondDate.GetDay() == 2);
	REQUIRE(date.GetDay() == 2);

	secondDate = --date;
	REQUIRE(secondDate.GetDay() == 1);
	REQUIRE(date.GetDay() == 1);

	date += 5;
	REQUIRE(date.GetDay() == 6);

	date -= 2;
	REQUIRE(date.GetDay() == 4);

	secondDate = date + 5;
	REQUIRE(secondDate.GetDay() == 9);
	REQUIRE(date.GetDay() == 4);

	secondDate = 5 + date;
	REQUIRE(secondDate.GetDay() == 9);
	REQUIRE(date.GetDay() == 4);

	secondDate = date - 2;
	REQUIRE(secondDate.GetDay() == 2);
	REQUIRE(date.GetDay() == 4);

	int days = date - date;
	REQUIRE(days == 0);
	REQUIRE(date.GetDay() == 4);

	days = secondDate - date;
	REQUIRE(days == -2);
	REQUIRE(date.GetDay() == 4);

	days = date - secondDate;
	REQUIRE(days == 2);
	REQUIRE(date.GetDay() == 4);
}

TEST_CASE("TestDatePlusMinusOperationsFailed")
{
	CDate date(31, Month::DECEMBER, 9999);
	REQUIRE_THROWS_AS(date++, DateOutOfRangeException);
	REQUIRE_THROWS_AS(++date, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date += 1, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date -= -1, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date + 1, DateOutOfRangeException);
	REQUIRE_THROWS_AS(1 + date, DateOutOfRangeException);

	date = CDate();
	REQUIRE_THROWS_AS(date--, DateOutOfRangeException);
	REQUIRE_THROWS_AS(--date, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date -= 1, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date += -1, DateOutOfRangeException);
	REQUIRE_THROWS_AS(date - 1, DateOutOfRangeException);
}

TEST_CASE("TestDateComparisonOperationsSuccess")
{
	CDate firstDate(1000);
	CDate secondDate(2000);
	REQUIRE(firstDate < secondDate);
	REQUIRE(firstDate <= secondDate);
	REQUIRE(firstDate != secondDate);
	REQUIRE_FALSE(firstDate > secondDate);
	REQUIRE_FALSE(firstDate >= secondDate);
	REQUIRE_FALSE(firstDate == secondDate);

	firstDate = CDate(2000);
	REQUIRE(firstDate == secondDate);
	REQUIRE(firstDate >= secondDate);
	REQUIRE(firstDate <= secondDate);
	REQUIRE_FALSE(firstDate < secondDate);
	REQUIRE_FALSE(secondDate < firstDate);
	REQUIRE_FALSE(firstDate != secondDate);
}

TEST_CASE("TestDateInputOutputSuccess")
{
	std::stringstream input;
	std::stringstream output;

	input.str("01-01-2023");
	CDate date;
	input >> date;
	REQUIRE(input.fail() == false);
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 2023);

	output << date;
	REQUIRE(output.str() == "01-01-2023");

	input.clear();
	input.str("1-1-1975");
	input >> date;
	REQUIRE(input.fail() == false);
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetYear() == 1975);

	output.str("");
	output << date;
	REQUIRE(output.str() == "01-01-1975");

	input.clear();
	input.str("12-12-9999");
	input >> date;
	REQUIRE(input.fail() == false);
	REQUIRE(date.GetDay() == 12);
	REQUIRE(date.GetMonth() == Month::DECEMBER);
	REQUIRE(date.GetYear() == 9999);
}

TEST_CASE("TestDateInputOutputFailed")
{
	std::stringstream input;

	input.str("01-00-2023");
	CDate date;
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("01-13-2023");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("40-12-2023");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("01-12-100000");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("0-12-2023");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("12-1.2-2025");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("1.2-12-2025");
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input >> date;
	REQUIRE(input.fail() == true);

	input.clear();
	input.str("");
	input >> date;
	REQUIRE(input.fail() == true);
}

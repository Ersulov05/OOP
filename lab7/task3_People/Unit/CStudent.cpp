#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../src/CStudent.h"
#include "../../../catch/catch.hpp"

TEST_CASE("TestCreateCStudent")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");

	REQUIRE(student.GetFirstName() == "Andrey");
	REQUIRE(student.GetSecondName() == "Ersulov");
	REQUIRE(student.GetThirdName() == "Aleksandrovich");
	REQUIRE(student.GetAddres() == "Addres");
	REQUIRE(student.GetUniversityName() == "Volgatech");
	REQUIRE(student.GetStudentTicketNumber() == "1234");
}

TEST_CASE("TestSetFirstName")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetFirstName() == "Andrey");

	student.SetFirstName("AndreyAndrey");
	REQUIRE(student.GetFirstName() == "AndreyAndrey");
}

TEST_CASE("TestSetSecondName")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetSecondName() == "Ersulov");

	student.SetSecondName("ErsulovErsulov");
	REQUIRE(student.GetSecondName() == "ErsulovErsulov");
}

TEST_CASE("TestSetThirdName")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetThirdName() == "Aleksandrovich");

	student.SetThirdName("AleksandrovichAleksandrovich");
	REQUIRE(student.GetThirdName() == "AleksandrovichAleksandrovich");
}

TEST_CASE("TestSetAddress")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetAddres() == "Addres");

	student.SetAddress("AddresAddres");
	REQUIRE(student.GetAddres() == "AddresAddres");
}

TEST_CASE("TestSetUniversityName")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetUniversityName() == "Volgatech");

	student.SetUniversityName("VolgatechVolgatech");
	REQUIRE(student.GetUniversityName() == "VolgatechVolgatech");
}

TEST_CASE("TestSetStudentTicketNumber")
{
	CStudent student = CStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234");
	REQUIRE(student.GetStudentTicketNumber() == "1234");

	student.SetStudentTicketNumber("12341234");
	REQUIRE(student.GetStudentTicketNumber() == "12341234");
}
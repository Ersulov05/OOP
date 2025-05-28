#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../src/CAdvancedStudent.h"
#include "../../../catch/catch.hpp"

TEST_CASE("TestCreateCAdvancedStudent")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");

	REQUIRE(advancedStudent.GetFirstName() == "Andrey");
	REQUIRE(advancedStudent.GetSecondName() == "Ersulov");
	REQUIRE(advancedStudent.GetThirdName() == "Aleksandrovich");
	REQUIRE(advancedStudent.GetAddres() == "Addres");
	REQUIRE(advancedStudent.GetUniversityName() == "Volgatech");
	REQUIRE(advancedStudent.GetStudentTicketNumber() == "1234");
	REQUIRE(advancedStudent.GetDissertationTheme() == "OOP");
}

TEST_CASE("TestSetFirstName")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetFirstName() == "Andrey");

	advancedStudent.SetFirstName("AndreyAndrey");
	REQUIRE(advancedStudent.GetFirstName() == "AndreyAndrey");
}

TEST_CASE("TestSetSecondName")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetSecondName() == "Ersulov");

	advancedStudent.SetSecondName("ErsulovErsulov");
	REQUIRE(advancedStudent.GetSecondName() == "ErsulovErsulov");
}

TEST_CASE("TestSetThirdName")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetThirdName() == "Aleksandrovich");

	advancedStudent.SetThirdName("AleksandrovichAleksandrovich");
	REQUIRE(advancedStudent.GetThirdName() == "AleksandrovichAleksandrovich");
}

TEST_CASE("TestSetAddress")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetAddres() == "Addres");

	advancedStudent.SetAddress("AddresAddres");
	REQUIRE(advancedStudent.GetAddres() == "AddresAddres");
}

TEST_CASE("TestSetUniversityName")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetUniversityName() == "Volgatech");

	advancedStudent.SetUniversityName("VolgatechVolgatech");
	REQUIRE(advancedStudent.GetUniversityName() == "VolgatechVolgatech");
}

TEST_CASE("TestSetStudentTicketNumber")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetStudentTicketNumber() == "1234");

	advancedStudent.SetStudentTicketNumber("12341234");
	REQUIRE(advancedStudent.GetStudentTicketNumber() == "12341234");
}

TEST_CASE("TestSetDissertationTheme")
{
	CAdvancedStudent advancedStudent = CAdvancedStudent("Andrey", "Ersulov", "Aleksandrovich", "Addres", "Volgatech", "1234", "OOP");
	REQUIRE(advancedStudent.GetDissertationTheme() == "OOP");

	advancedStudent.SetDissertationTheme("OOPOOP");
	REQUIRE(advancedStudent.GetDissertationTheme() == "OOPOOP");
}
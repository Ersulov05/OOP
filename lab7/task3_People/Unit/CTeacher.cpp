#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../src/CTeacher.h"
#include "../../../catch/catch.hpp"

TEST_CASE("TestCreateCTeacher")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");

	REQUIRE(teacher.GetFirstName() == "Andrey");
	REQUIRE(teacher.GetSecondName() == "Ersulov");
	REQUIRE(teacher.GetThirdName() == "Aleksandrovich");
	REQUIRE(teacher.GetAddres() == "Addres");
	REQUIRE(teacher.GetSubjectName() == "OOP");
}

TEST_CASE("TestSetFirstName")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(teacher.GetFirstName() == "Andrey");

	teacher.SetFirstName("AndreyAndrey");
	REQUIRE(teacher.GetFirstName() == "AndreyAndrey");
}

TEST_CASE("TestSetSecondName")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(teacher.GetSecondName() == "Ersulov");

	teacher.SetSecondName("ErsulovErsulov");
	REQUIRE(teacher.GetSecondName() == "ErsulovErsulov");
}

TEST_CASE("TestSetThirdName")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(teacher.GetThirdName() == "Aleksandrovich");

	teacher.SetThirdName("AleksandrovichAleksandrovich");
	REQUIRE(teacher.GetThirdName() == "AleksandrovichAleksandrovich");
}

TEST_CASE("TestSetAddress")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(teacher.GetAddres() == "Addres");

	teacher.SetAddress("AddresAddres");
	REQUIRE(teacher.GetAddres() == "AddresAddres");
}

TEST_CASE("TestSetSubjectName")
{
	CTeacher teacher = CTeacher("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(teacher.GetSubjectName() == "OOP");

	teacher.SetSubjectName("OOPOOP");
	REQUIRE(teacher.GetSubjectName() == "OOPOOP");
}
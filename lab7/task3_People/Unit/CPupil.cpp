#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../src/CPupil.h"
#include "../../../catch/catch.hpp"

TEST_CASE("TestCreateCPupil")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");

	REQUIRE(pupil.GetFirstName() == "Andrey");
	REQUIRE(pupil.GetSecondName() == "Ersulov");
	REQUIRE(pupil.GetThirdName() == "Aleksandrovich");
	REQUIRE(pupil.GetAddres() == "Addres");
	REQUIRE(pupil.GetSchoolName() == "#30");
	REQUIRE(pupil.GetClassName() == "11");
}

TEST_CASE("TestSetFirstName")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetFirstName() == "Andrey");

	pupil.SetFirstName("AndreyAndrey");
	REQUIRE(pupil.GetFirstName() == "AndreyAndrey");
}

TEST_CASE("TestSetSecondName")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetSecondName() == "Ersulov");

	pupil.SetSecondName("ErsulovErsulov");
	REQUIRE(pupil.GetSecondName() == "ErsulovErsulov");
}

TEST_CASE("TestSetThirdName")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetThirdName() == "Aleksandrovich");

	pupil.SetThirdName("AleksandrovichAleksandrovich");
	REQUIRE(pupil.GetThirdName() == "AleksandrovichAleksandrovich");
}

TEST_CASE("TestSetAddress")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetAddres() == "Addres");

	pupil.SetAddress("AddresAddres");
	REQUIRE(pupil.GetAddres() == "AddresAddres");
}

TEST_CASE("TestSetSchoolName")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetSchoolName() == "#30");

	pupil.SetSchoolName("#30#30");
	REQUIRE(pupil.GetSchoolName() == "#30#30");
}

TEST_CASE("TestSetClassName")
{
	CPupil pupil = CPupil("Andrey", "Ersulov", "Aleksandrovich", "Addres", "#30", "11");
	REQUIRE(pupil.GetClassName() == "11");

	pupil.SetClassName("1111");
	REQUIRE(pupil.GetClassName() == "1111");
}
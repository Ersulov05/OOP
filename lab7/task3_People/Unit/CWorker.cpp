#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../src/CWorker.h"
#include "../../../catch/catch.hpp"

TEST_CASE("TestCreateCWorker")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");

	REQUIRE(worker.GetFirstName() == "Andrey");
	REQUIRE(worker.GetSecondName() == "Ersulov");
	REQUIRE(worker.GetThirdName() == "Aleksandrovich");
	REQUIRE(worker.GetAddres() == "Addres");
	REQUIRE(worker.GetSpeciality() == "OOP");
}

TEST_CASE("TestSetFirstName")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(worker.GetFirstName() == "Andrey");

	worker.SetFirstName("AndreyAndrey");
	REQUIRE(worker.GetFirstName() == "AndreyAndrey");
}

TEST_CASE("TestSetSecondName")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(worker.GetSecondName() == "Ersulov");

	worker.SetSecondName("ErsulovErsulov");
	REQUIRE(worker.GetSecondName() == "ErsulovErsulov");
}

TEST_CASE("TestSetThirdName")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(worker.GetThirdName() == "Aleksandrovich");

	worker.SetThirdName("AleksandrovichAleksandrovich");
	REQUIRE(worker.GetThirdName() == "AleksandrovichAleksandrovich");
}

TEST_CASE("TestSetAddress")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(worker.GetAddres() == "Addres");

	worker.SetAddress("AddresAddres");
	REQUIRE(worker.GetAddres() == "AddresAddres");
}

TEST_CASE("TestSetSpeciality")
{
	CWorker worker = CWorker("Andrey", "Ersulov", "Aleksandrovich", "Addres", "OOP");
	REQUIRE(worker.GetSpeciality() == "OOP");

	worker.SetSpeciality("OOPOOP");
	REQUIRE(worker.GetSpeciality() == "OOPOOP");
}
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Car/Transmission/Exception/GearsNotLinkedException.h"
#include "../Car/Transmission/Exception/InvalidGearException.h"
#include "../Car/Transmission/Exception/NotForwardGearsException.h"
#include "../Car/Transmission/Exception/UncorrectFirstDriveGearException.h"
#include "../Car/Transmission/Exception/UncorrectGearshiftException.h"
#include "../Car/Transmission/Exception/UncorrectReverseGearException.h"
#include "../Car/Transmission/Exception/UnsuitableCurrentSpeedException.h"
#include "../Car/Transmission/Transmission.h"

TEST_CASE("TestCreateTransmissionSuccess")
{
	GearSpeedInterval reverseGearSpeedInterval = { 0, 20 };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { 0, 20 }, { 10, 30 } };
	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	driveGearSpeedIntervals = { { 0, 20 }, { 20, 30 } };
	transmission = Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	driveGearSpeedIntervals = { { 0, 20 }, { 0, 30 } };
	transmission = Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);
}

TEST_CASE("TestCreateTransmissionUncorrectReverseGearFailed")
{
	GearSpeedInterval reverseGearSpeedInterval = { 10, 20 };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { 0, 20 }, { 10, 30 } };
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), UncorrectReverseGearException);
}

TEST_CASE("TestCreateTransmissionNotForwardGearsFailed")
{
	GearSpeedInterval reverseGearSpeedInterval = { 0, 20 };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = {};
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), NotForwardGearsException);
}

TEST_CASE("TestCreateTransmissionGearsNotLinkedFailed")
{
	GearSpeedInterval reverseGearSpeedInterval = { 0, 20 };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { 0, 20 }, { 21, 30 } };
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), GearsNotLinkedException);

	driveGearSpeedIntervals = { { 0, 20 }, { 20, 30 }, { 10, 50 } };
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), GearsNotLinkedException);

	driveGearSpeedIntervals = { { 0, 20 }, { 20, 30 }, { 10, 25 } };
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), GearsNotLinkedException);

	driveGearSpeedIntervals = { { 0, 20 }, { 0, 20 } };
	REQUIRE_THROWS_AS(Transmission(reverseGearSpeedInterval, driveGearSpeedIntervals), GearsNotLinkedException);
}

TEST_CASE("TestWorkWithTransmissionSuccess")
{
	int reverseGearMinSpeed = 0;
	int reverseGearMaxSpeed = 20;
	int firstGearMinSpeed = 0;
	int firstGearMaxSpeed = 20;
	int secondGearMinSpeed = 10;
	int secondGearMaxSpeed = 30;

	GearSpeedInterval reverseGearSpeedInterval = { reverseGearMinSpeed, reverseGearMaxSpeed };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { firstGearMinSpeed, firstGearMaxSpeed }, { secondGearMinSpeed, secondGearMaxSpeed } };

	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	transmission.SetGear(1, 0, Direction::STANDING_STILL);
	Gear currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 1);
	REQUIRE(currentGear.GetGearType() == GearType::DRIVE);
	REQUIRE(currentGear.GetMinSpeed() == firstGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == firstGearMaxSpeed);

	transmission.SetGear(2, 10, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 2);
	REQUIRE(currentGear.GetGearType() == GearType::DRIVE);
	REQUIRE(currentGear.GetMinSpeed() == secondGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == secondGearMaxSpeed);

	transmission.SetGear(2, 20, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 2);
	REQUIRE(currentGear.GetGearType() == GearType::DRIVE);
	REQUIRE(currentGear.GetMinSpeed() == secondGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == secondGearMaxSpeed);

	transmission.SetGear(1, 20, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 1);
	REQUIRE(currentGear.GetGearType() == GearType::DRIVE);
	REQUIRE(currentGear.GetMinSpeed() == firstGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == firstGearMaxSpeed);

	transmission.SetGear(0, 20, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(currentGear.GetGearType() == GearType::NEUTRAL);
	REQUIRE(currentGear.GetMinSpeed() == std::nullopt);
	REQUIRE(currentGear.GetMaxSpeed() == std::nullopt);

	transmission.SetGear(2, 20, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 2);
	REQUIRE(currentGear.GetGearType() == GearType::DRIVE);
	REQUIRE(currentGear.GetMinSpeed() == secondGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == secondGearMaxSpeed);

	transmission.SetGear(0, 20, Direction::FORWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(currentGear.GetGearType() == GearType::NEUTRAL);
	REQUIRE(currentGear.GetMinSpeed() == std::nullopt);
	REQUIRE(currentGear.GetMaxSpeed() == std::nullopt);

	transmission.SetGear(-1, 0, Direction::STANDING_STILL);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == -1);
	REQUIRE(currentGear.GetGearType() == GearType::REVERSE);
	REQUIRE(currentGear.GetMinSpeed() == reverseGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == reverseGearMaxSpeed);

	transmission.SetGear(-1, 20, Direction::BACKWARD);
	currentGear = transmission.GetCurrentGear();
	REQUIRE(transmission.GetCurrentGearNumber() == -1);
	REQUIRE(currentGear.GetGearType() == GearType::REVERSE);
	REQUIRE(currentGear.GetMinSpeed() == reverseGearMinSpeed);
	REQUIRE(currentGear.GetMaxSpeed() == reverseGearMaxSpeed);
}

TEST_CASE("TestWorkWithTransmissionInvalidGearFailed")
{
	int reverseGearMinSpeed = 0;
	int reverseGearMaxSpeed = 20;
	int firstGearMinSpeed = 0;
	int firstGearMaxSpeed = 20;

	GearSpeedInterval reverseGearSpeedInterval = { reverseGearMinSpeed, reverseGearMaxSpeed };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { firstGearMinSpeed, firstGearMaxSpeed } };

	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	REQUIRE_THROWS_AS(transmission.SetGear(2, 0, Direction::STANDING_STILL), InvalidGearException);
	REQUIRE_THROWS_AS(transmission.SetGear(-2, 0, Direction::STANDING_STILL), InvalidGearException);
}

TEST_CASE("TestWorkWithTransmissionUnsuitableCurrentSpeedFailed")
{
	int reverseGearMinSpeed = 0;
	int reverseGearMaxSpeed = 20;
	int firstGearMinSpeed = 0;
	int firstGearMaxSpeed = 20;
	int secondGearMinSpeed = 10;
	int secondGearMaxSpeed = 30;

	GearSpeedInterval reverseGearSpeedInterval = { reverseGearMinSpeed, reverseGearMaxSpeed };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { firstGearMinSpeed, firstGearMaxSpeed }, { secondGearMinSpeed, secondGearMaxSpeed } };

	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	REQUIRE_THROWS_AS(transmission.SetGear(1, 30, Direction::FORWARD), UnsuitableCurrentSpeedException);
	REQUIRE_THROWS_AS(transmission.SetGear(2, 0, Direction::STANDING_STILL), UnsuitableCurrentSpeedException);
}

TEST_CASE("TestWorkWithTransmissionUncorrectGearshiftFailed")
{
	int reverseGearMinSpeed = 0;
	int reverseGearMaxSpeed = 20;
	int firstGearMinSpeed = 0;
	int firstGearMaxSpeed = 20;
	int secondGearMinSpeed = 10;
	int secondGearMaxSpeed = 30;

	GearSpeedInterval reverseGearSpeedInterval = { reverseGearMinSpeed, reverseGearMaxSpeed };
	std::vector<GearSpeedInterval> driveGearSpeedIntervals = { { firstGearMinSpeed, firstGearMaxSpeed }, { secondGearMinSpeed, secondGearMaxSpeed } };

	Transmission transmission(reverseGearSpeedInterval, driveGearSpeedIntervals);
	REQUIRE(transmission.GetCurrentGearNumber() == 0);
	REQUIRE(transmission.GetCurrentGear().GetGearType() == GearType::NEUTRAL);

	REQUIRE_THROWS_AS(transmission.SetGear(-1, 30, Direction::FORWARD), UncorrectGearshiftException);

	transmission.SetGear(-1, 0, Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(transmission.SetGear(1, 20, Direction::BACKWARD), UncorrectGearshiftException);

	transmission.SetGear(1, 0, Direction::STANDING_STILL);
	REQUIRE_THROWS_AS(transmission.SetGear(-1, 20, Direction::FORWARD), UncorrectGearshiftException);
}
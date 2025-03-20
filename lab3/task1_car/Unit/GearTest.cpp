#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Car/Transmission/Gear/Exception/InvalidGearSpeedLimitsException.h"
#include "../Car/Transmission/Gear/Exception/NegativeGearSpeedException.h"
#include "../Car/Transmission/Gear/Exception/UnCorrectGearTypeWithSpeedLimitsException.h"
#include "../Car/Transmission/Gear/Gear.h"

TEST_CASE("TestCreateGear")
{
	Gear gear = Gear(GearType::NEUTRAL, std::nullopt, std::nullopt);
	REQUIRE(gear.GetGearType() == GearType::NEUTRAL);
	REQUIRE(gear.GetMinSpeed() == std::nullopt);
	REQUIRE(gear.GetMaxSpeed() == std::nullopt);

	gear = Gear(GearType::DRIVE, 0, 100);
	REQUIRE(gear.GetGearType() == GearType::DRIVE);
	REQUIRE(gear.GetMinSpeed() == 0);
	REQUIRE(gear.GetMaxSpeed() == 100);

	gear = Gear(GearType::REVERSE, 0, 50);
	REQUIRE(gear.GetGearType() == GearType::REVERSE);
	REQUIRE(gear.GetMinSpeed() == 0);
	REQUIRE(gear.GetMaxSpeed() == 50);

	REQUIRE_THROWS_AS(Gear(GearType::DRIVE, 20, 0), InvalidGearSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::REVERSE, -5, 0), NegativeGearSpeedException);
	REQUIRE_THROWS_AS(Gear(GearType::DRIVE, 0, -1), NegativeGearSpeedException);

	REQUIRE_THROWS_AS(Gear(GearType::DRIVE, std::nullopt, 0), UnCorrectGearTypeWithSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::REVERSE, 0, std::nullopt), UnCorrectGearTypeWithSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::DRIVE, std::nullopt, std::nullopt), UnCorrectGearTypeWithSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::NEUTRAL, std::nullopt, 0), UnCorrectGearTypeWithSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::NEUTRAL, 0, std::nullopt), UnCorrectGearTypeWithSpeedLimitsException);
	REQUIRE_THROWS_AS(Gear(GearType::NEUTRAL, 0, 10), UnCorrectGearTypeWithSpeedLimitsException);
}
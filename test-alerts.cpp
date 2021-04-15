#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the no breach according to limits and sending to Console") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "NORMAL_PASSIVE_COOLING"};
  REQUIRE(checkAndAlert(TO_CONSOLE, batteryChar, 35) == ALERT_SUCCESS);
}

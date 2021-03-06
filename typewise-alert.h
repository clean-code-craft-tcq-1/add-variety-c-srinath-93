#pragma once

#define LOWER_LIMIT (double)0.0
#define PASSIVE_COOLING_UPPER_LIMIT (double)35.0
#define HI_ACTIVE_COOLING_UPPER_LIMIT (double)45.0
#define MED_ACTIVE_COOLING_UPPER_LIMIT (double)40.0
typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE
} AlertTarget;

typedef enum
{
  ALERT_FAILURE,
  ALERT_SUCCESS
}AlertRetStatus;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
  double lowerLimit;
  double upperLimit;
}LimitDetail_st;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
AlertRetStatus checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

AlertRetStatus sendToController(BreachType breachType);
AlertRetStatus sendToEmail(BreachType breachType);
AlertRetStatus sendToConsole(BreachType breachType);

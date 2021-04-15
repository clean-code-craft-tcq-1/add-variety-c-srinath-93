#pragma once

#define LOWER_LIMIT 0
#define PASSIVE_COOLING_UPPER_LIMIT 35
#define HI_ACTIVE_COOLING_UPPER_LIMIT 45
#define MED_ACTIVE_COOLING_UPPER_LIMIT 40
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

LimitDetail_st classifyTemperatureBreach[] = {{LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT},{LOWER_LIMIT,HI_ACTIVE_COOLING_UPPER_LIMIT},{LOWER_LIMIT,MED_ACTIVE_COOLING_UPPER_LIMIT}};
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
AlertRetStatus checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

AlertRetStatus sendToController(BreachType breachType);
AlertRetStatus sendToEmail(BreachType breachType);
AlertRetStatus(*AlertType[])(BreachType) = {sendToController, sendToEmail, sendToController};

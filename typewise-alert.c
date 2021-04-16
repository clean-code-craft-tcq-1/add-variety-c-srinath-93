#include "typewise-alert.h"
#include <stdio.h>
LimitDetail_st classifyTemperatureBreach[] = {{LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT},{LOWER_LIMIT,HI_ACTIVE_COOLING_UPPER_LIMIT},{LOWER_LIMIT,MED_ACTIVE_COOLING_UPPER_LIMIT}};
AlertRetStatus(*AlertType[])(BreachType) = {sendToController, sendToEmail, sendToController};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

AlertRetStatus sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return ALERT_SUCCESS;
}

AlertRetStatus sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  AlertRetStatus statusRet = ALERT_FAILURE;
  switch(breachType){
    case TOO_LOW:
      printf("To: %s\n Hi, the temperature is too low\n", recepient);
      statusRet = ALERT_SUCCESS;
      break;
    case TOO_HIGH:
      printf("To: %s\n Hi, the temperature is too high\n",recepient);
      statusRet = ALERT_SUCCESS;
      break;
    case NORMAL:
      statusRet = ALERT_SUCCESS;
      break;
  }
  return statusRet;
}
AlertRetStatus sendToConsole(BreachType breachType) {
  printf("Breach Types Lookup -\nNORMAL - 0 \nTOO_LOW - 1 \nTOO_HIGH - 2 \nThe current breach type is %d \n",breachType);
  return ALERT_SUCCESS;
}
AlertRetStatus checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  AlertRetStatus checkAlertRetStatus;
  BreachType typeOfBreach = inferBreach(temperatureInC, classifyTemperatureBreach[batteryChar.coolingType].lowerLimit, classifyTemperatureBreach[batteryChar.coolingType].upperLimit);
  checkAlertRetStatus = AlertType[alertTarget](typeOfBreach);
  return checkAlertRetStatus;
}

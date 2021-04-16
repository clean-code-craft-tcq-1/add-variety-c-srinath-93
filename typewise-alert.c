#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

AlertRetStatus sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  retrun ALERT_SUCCESS;
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
      default:
      /* Do nothing */
      break;  
  }
  return statusRet;
}
AlertRetStatus sendToConsole(BreachType breachType) {
  printf("Breach Types Lookup -\nNORMAL - 0 \nTOO_LOW - 1 \nTOO_HIGH - 2 \nThe current breach type is %d \n",breachType);
  return ALERT_SUCCESS;
}
AlertRetStatus checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  AlertRetStatus checkAlertRetStatus;
  BreachType breachType = inferBreach(temperatureInC, classifyTemperatureBreach[batteryChar.coolingType].lowerLimit, 
                                      classifyTemperatureBreach[batteryChar.coolingType].upperLimit);
  checkAlertRetStatus = AlertType[alertTarget](BreachType);
  return checkAlertRetStatus;
}

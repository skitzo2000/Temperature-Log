#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Defining Temp probe addresses, Note I use static addresses rather than just poling for all probes on the bus line as its quicker.
DeviceAddress ambientThermometer = { 0x28, 0x6A, 0x45, 0x44, 0x2, 0x0, 0x0, 0x88 };
DeviceAddress fermenter1Thermometer   = { 0x28, 0x45, 0x19, 0x5F, 0x2, 0x0, 0x0, 0x2 };
DeviceAddress fermenter2Thermometer   = { 0x28, 0xA, 0xEF, 0x5E, 0x2, 0x0, 0x0, 0xE6 };
//Serial Read variable
int incomingByte = 0;
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(ambientThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(fermenter1Thermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(fermenter2Thermometer, TEMPERATURE_PRECISION);
}
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(tempC);
}
// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  printTemperature(deviceAddress);
  Serial.print("\t");
}
void printStatus()
{
  sensors.requestTemperatures();
  printData(ambientThermometer);
  printData(fermenter1Thermometer);
  printData(fermenter2Thermometer);
  Serial.println("");
}

void loop(void)
{ 
  if (Serial.available() > 0) {
      incomingByte = Serial.read();
      if (incomingByte == 49){
        printStatus();
      } 
  }
}


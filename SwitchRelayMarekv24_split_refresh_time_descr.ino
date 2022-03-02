// Enable debug prints to serial monitor
#define MY_DEBUG

// Use a bit lower baudrate for serial prints on ESP8266 than default in MyConfig.h
//#define MY_BAUD_RATE 9600
// Define a lower baud rate for Arduino's running on 8 MHz (Arduino Pro Mini 3.3V & SenseBender)
#if F_CPU == 8000000L
#define MY_BAUD_RATE 38400
#endif

#define MY_TRANSPORT_WAIT_READY_MS 1

// uncomment if we want to manually assign an ID
#define MY_NODE_ID 13


// !!!! CHOOSE ONLY ONE !!!!

//#include "ESPGateway.h" // for ESP8266 WiFi gateway -> set your WiFi in ESPGateway.h tab!
#include "SerialGateway.h" // for Serial gateway
//#include "RF24Gateway.h" // for RF24 radio gateway
//#include "MQTTGateway.h" // for MQTT Ethernet gateway



#include <Bounce2.h>
//#include <PMButton.h>
#include <MySensors.h>
#include <SPI.h>

#include "SwitchRelay.h"

/* define your SwitchRelay objects here
 SwitchRelay(int childId      // Cover/Roller Shutter device ID for MySensors and Controller (Domoticz, HA etc)
              , int setIdUp     // Roll time UP setpoint device ID for MySensors and Controller (Domoticz, HA etc)
              , int setIdDown   // Roll time DOWN setpointdevice ID for MySensors and Controller (Domoticz, HA etc)
              , int initId      // Initialization device ID for MySensors and Controller (Domoticz, HA etc)
              , int buttonUp    // Button Pin for UP
              , int buttonDown  // Button Pin for DOWN
              , int relayUp     // Relay Pin for UP
              , int relayDown   // Relay Pin for DOWN
              , uint8_t initTimeUp          // Initial Roll time UP
              , uint8_t initTimeDown        // Initial Roll time DOWN
              , uint8_t initCalibrationTime // Initial calibration time (time that relay stay ON after reach 0 or 100%)
              , int debaunceTime            // Time to debounce button -> standard = 50
              , bool invertedRelay          // for High level trigger = 0; for Low level trigger = 1
              )
*/

bool service = 0;
int servicePin = 2;
int serviceLedPin = 13; // built-in LED

SwitchRelay lights[] =
{
  {1, 9, 11, 50, 1, "switch 1"},
  {2, 10, 12, 50, 1, "switch 2"}
};

const int lightsCount = sizeof(lights) / sizeof(SwitchRelay);

void setup() 
{ 
  // Service Mode input = D2 -> only if pass-through mode is needed, f.e. for programming, blinking etc.
  pinMode(servicePin, INPUT_PULLUP);
  service = !digitalRead(servicePin);
  pinMode(serviceLedPin, OUTPUT);
  digitalWrite(serviceLedPin, service);
  
  // Setup locally attached sensors
  wait(5000);
  for(int i = 0; i < lightsCount; i++)
  {
    lights[i].SyncController(); 
    if(service)
    {
      lights[i].enterServiceMode(); 
    }
  }
}

void presentation()  
{   
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("lights by Marek", "22.0");
  for(int i = 0; i < lightsCount; i++)
  {
    lights[i].Present(); 
  }
}

void loop() 
{ 
  for(int i = 0; i < lightsCount; i++)
  {
    lights[i].Update(); 
  }
}

void receive(const MyMessage &message) 
{
  for(int i = 0; i < lightsCount; i++)
  {
    lights[i].Receive(message); 
  }
}

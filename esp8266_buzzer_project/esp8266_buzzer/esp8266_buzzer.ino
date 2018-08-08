// include ESP8266Wifi library
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiUdp.h>

// include aREST library
#include <aREST.h>

// define a LISTEN_PORT for wifi
// this is a port for listening for incoming TCP connections
#define LISTEN_PORT 80

// create aREST instance
aREST rest = aREST();

// Wifi parameters including name and password to connet
const char * ssid = "lai khoi";
const char * password = "09012001";
// define a pin for my led, actually I only have one PIN for LED, which is GPIO2
const int pin = 2;

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// variable to show on the webpage
int temperature;
int humidity;

void setup() {
  // put your setup code here, to run once:

  // Start a serial
  Serial.begin(115200);
  // define the GPIO2 as OUTPUT to control the LED
  pinMode(pin, OUTPUT);
  // for the buzzer, HIGH will make the buzzer silent. Therefore, default for the buzzer should be silent
  digitalWrite(pin, HIGH);

  // init some value to show on the webpage
  temperature = 30;
  humidity = 80;

  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // add a function to control led
  rest.function("led",ledControl);

  // give a name and ID to the device
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to the Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);
}

int ledControl(String command)
{
  int state = command.toInt();
  // for the buzzer, when the user press the only button, it should make the buzzer speaks for 0.5 seconds then keeps silent again
  if(state == 0)
  {
    digitalWrite(pin, LOW);
    delay(500);
  }
  // continue to keep silent
  digitalWrite(pin, HIGH);
  return 1;
}

/*
 * Everything you need about ESP8266, refer at ../arduino_esp8266/arduino_esp8266.ino
 * About the rest.function, you can see the reference at ../Ethernet_connection/Ethernet_connection.ino
 * In this file, I gonna control the LED through ESP8266v1
 */

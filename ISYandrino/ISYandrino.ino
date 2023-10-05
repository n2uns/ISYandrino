/*
version 0.0.1
  this will be my lib for adding esp32 modules to my universal devices controlers 
*/
#include <ArduinoJson.h>
#include "EspMQTTClient.h"
String message;
String statmessage;
const int Analogin = 36;
const int DigIn = 23;
const int Digout = 16;
const int Bultinled = 2;
char Device[] = "mydevice";
DynamicJsonDocument  doc(1024);
DynamicJsonDocument  mystat(1024);
int me;


EspMQTTClient client(
  "espdevices",
  "Kevin8386",
  "192.168.18.185",  // MQTT Broker server ip
  "admin",   // Can be omitted if not needed
  "kevin8386",   // Can be omitted if not needed
  Device,     // Client name that uniquely identify your device
  1884              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
Serial.begin(115200);
doc["AI1"] = "Battery Voltage";
doc["AO1"] = "Light output";
doc["DO1"] = "Batt Charger";
doc["DO2"] = "Light";
serializeJson(doc, message);

mystat["AI1"] = 13.6;
mystat["AO1"] = 125;
mystat["DO1"] = 100;
mystat["DO2"] = 0;
serializeJson(mystat, statmessage);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
 
  //client.enableLastWillMessage( toCharArray(mesg) , "I am going offline");  // You can activate the retain flag by setting the third parameter to true
  pinMode (Digout, OUTPUT);
  pinMode (DigIn, INPUT);
 
 }

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
 String mesg;
 mesg = Device;
 //String mesg;
 //char mesg[] = Device;
   IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe(mesg + "/cmd", [](const String & payload) {
    Serial.println("fron cmd" + payload);
 // if 
    digitalWrite( Bultinled, payload.toInt() );
  //  digitalWrite( Bultinled, HIGH );
  });

  // Subscribe to "mydevice/status" and display received message to Serial
  client.subscribe(mesg + "/status", [](const String & topic, const String & payload) {
    Serial.println("(From status) topic: " + topic + ", payload: " + payload);
    digitalWrite( Digout, payload.toInt() );
  });

   // Subscribe to "mydevice/Discovery/#" and display received message to Serial
  client.subscribe(mesg + "/Discovery", [](const String & topic, const String & payload) {
  String mesg;
 mesg = Device;
 if (payload == "1")
 {
  client.publish(mesg + "/Discovery", message ); // You can activate the retain flag by setting the third parameter to true
}});

  // Execute delayed instructions
 // client.executeDelayed(5 * 1000, []() {
 //   client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
 // });
}

void loop()
{
 String mesg;
 mesg = Device;
   client.loop();
  me = me + 1;
  // Execute delayed instructions

if (me >= 24000)   {
client.publish(mesg + "/status", statmessage);
me=0;
 //client.publish(mesg + "/cmd", "my cmd is " + String( digitalRead( Digout )));
// Publish a message to "mytopic/Discovery"
  Serial.println(me);

}
  Serial.println(me);

}



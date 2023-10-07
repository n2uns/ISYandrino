 #include "ISYarduino.h"

String message;
String statmessage;

char Device[] = "mydevice";

EspMQTTClient* isyclient;
 
isyMQTT::isyMQTT(EspMQTTClient* myclient)
    {

isyclient = myclient;
    pincount = 1;
    analogcount = 0;
    analogoutcount = 0;
    digitaloutcount = 0;
    digitalincount = 0;
  
  myclient->enableDebuggingMessages(); // Enable debugging messages sent to serial output
  myclient->enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  myclient->enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
 


    };

void isyMQTT::start(int analogin, int analogout, int digitalin, int digitalout)
{
  totalpins = analogin + analogout + digitalin + digitalout;

}

void isyMQTT::analoginput( int &var1 , char displayname1[]
)
{
    analogcount++;
    doc["AI" + String(analogcount)] = displayname1;
    analoginval[analogcount] = *analoginval;
}


void isyMQTT::analogoutput( int &analogoutvar1 , char displayname1[]
)
{
    analogoutcount++;
    doc["AO" + String(analogoutcount)] = displayname1;
    analogoutval[analogoutcount] = *analogoutval;
}

void isyMQTT::digitalinput( int &digitalinvar1 , char displayname1[]
)
{
    digitalincount++;
    doc["DI" + String(digitalincount)] = displayname1;
    analoginval[digitalincount] = *digitalinval;
}

void isyMQTT::digitaloutput( int &digitaloutvar1 , char displayname1[]
)
{
    digitaloutcount++;
    doc["DO" + String(digitaloutcount)] = displayname1;
    analogoutval[digitaloutcount] = *digitaloutval;
}

void isyMQTT::run(void)
{
serializeJson(doc, message);
  // Optional functionalities of EspMQTTClient
  //client.enableLastWillMessage( toCharArray(mesg) , "I am going offline");  // You can activate the retain flag by setting the third parameter to true

}

void isyMQTT::loop(void)
{
  isyclient->loop();

}

void onConnectionEstablished()
{
String mesg;
 mesg = Device;
 int me;
   IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 // Subscribe to "mytopic/test" and display received message to Serial
isyclient->subscribe(mesg + "/cmd", [](const String & payload) {
    Serial.println("fron cmd" + payload);
  });

  // Subscribe to "mydevice/status" and display received message to Serial
  isyclient->subscribe(mesg + "/status", [](const String & topic, const String & payload) {
    Serial.println("(From status) topic: " + topic + ", payload: " + payload);
  });

   // Subscribe to "mydevice/Discovery/#" and display received message to Serial
isyclient->subscribe(mesg + "/Discovery", [](const String & topic, const String & payload) {
  String mesg;
 mesg = Device;
 if (payload == "1")
            {
            isyclient->publish(mesg + "/Discovery", message ); // You can activate the retain flag by setting the third parameter to true
//            Serial.println("(From status) topic: " + topic + ", payload: " + message);
            }
});

}

 
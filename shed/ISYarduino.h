#include <ArduinoJson.h>
#include "EspMQTTClient.h"


// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient



class isyMQTT {
 
 public:
      isyMQTT(EspMQTTClient* myclient);

void start(int analogin, int analogout, int digitalin, int digitalout);
void analoginput( int* var1 , char displayname1[]);
void analogoutput( int* analogoutvar1 , char displayname1[]);
void digitalinput( int* digitalinvar1 , char displayname1[]);
void digitaloutput( int* digitaloutvar1 , char displayname1[]);
void run(isyMQTT* mymqtt, char mydevice[]);
void loop(void);

int pincount;
int totalpins;

 private:
StaticJsonDocument<1024> doc;
StaticJsonDocument<1024> mystatus;
EspMQTTClient myclient;
int analogcount;
int *var1 = NULL;
int *analoginval[6];
int *analogoutvar1;

int digitalincount;
int *digitalinval[6];
int *digitalinvar1;
int *digitaloutvar1;

int lastanaloginval[5];
int lastanalogoutval[5];
int lastdigitalinval[5];
int lastdigitaloutval[5];

public:

int analogoutcount = 0;
int *analogoutval[6];
int digitaloutcount = 0;
int *digitaloutval[6];


};

// #include "ISYarduino.h"

String message;
String statmessage;
int setupdone = 0;

String(Device);

EspMQTTClient* isyclient;
isyMQTT* isymqtt;
 
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

void isyMQTT::analoginput( int *var1 , char displayname1[]
)
{
    analogcount++;
    doc["AI" + String(analogcount)] = displayname1;
    analoginval[analogcount] = var1;
}


void isyMQTT::analogoutput( int *analogoutvar1 , char displayname1[]
)
{
    analogoutcount++;
    doc["AO" + String(analogoutcount)] = displayname1;
    analogoutval[analogoutcount] = analogoutvar1;
}

void isyMQTT::digitalinput( int *digitalinvar1 , char displayname1[]
)
{
    digitalincount++;
    doc["DI" + String(digitalincount)] = displayname1;
    digitalinval[digitalincount] = digitalinvar1;
}

void isyMQTT::digitaloutput( int *digitaloutvar1 , char displayname1[]
)
{
    digitaloutcount++;
    doc["DO" + String(digitaloutcount)] = displayname1;
    digitaloutval[digitaloutcount] = digitaloutvar1;
}

void isyMQTT::run(isyMQTT* mymqtt, char mydevice[])
{
isymqtt = mymqtt;
Device = mydevice;
serializeJson(doc, message);


}

void isyMQTT::loop(void)               //////////////////////////  main loop check for changes in any of the io's and publish them to the node server
{
  isyclient->loop();
float thevalue;
String mesg;
 mesg = Device;
String dataoutput;
int newdataflage = 0;
 mesg = Device;
  pincount = 1;
  ///////////////////////////////////// analog in
  if ((analogcount != 0) && (setupdone == 1))
     {
      while (pincount <= analogcount)
          {
           thevalue =  *analoginval[pincount];
            if (thevalue != lastanaloginval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["AI" + String(pincount)] = (*analoginval[pincount] / 100.00);
  Serial.println("here " + String(*analoginval[pincount] / 100) + " from AI output");

              lastanaloginval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    }
  ///////////////////////////////////// analog out
    pincount = 1; 
  if ((analogoutcount != 0) && (setupdone == 1))
     {
      while (pincount <= analogoutcount)
          {
           thevalue =  *analogoutval[pincount];
           if (thevalue != lastanalogoutval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["AO" + String(pincount)] = (*analogoutval[pincount] / 100.00);
// Serial.println("here " + String(tmpval) + " from AO output");
              lastanalogoutval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    }
  ///////////////////////////////////// digital in
     pincount = 1; 
 if ((digitalincount != 0) && (setupdone == 1))
     {
      while (pincount <= digitalincount)
          {
           thevalue =  *digitalinval[pincount];
 // Serial.println(pincount);
           if (thevalue != lastdigitalinval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["DI" + String(pincount)] = *digitalinval[pincount];
 
              lastdigitalinval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    }
    pincount = 1; 
  ///////////////////////////////////// digital out
  if ((digitaloutcount != 0) && (setupdone == 1))
     {
      while (pincount <= digitaloutcount)
          {
           thevalue =  *digitaloutval[pincount];
 // Serial.println(pincount);
           if (thevalue != lastdigitaloutval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["DO" + String(pincount)] = *digitaloutval[pincount];
 
              lastdigitaloutval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    }
    pincount = 1; 
if (newdataflage == 1)
{

serializeJson(mystatus, statmessage);
isyclient->publish(mesg + "/status", statmessage ); // You can activate the retain flag by setting the third parameter to true

               Serial.println(statmessage + "from publish ");
statmessage = "";
newdataflage = 0;
}

}

void onConnectionEstablished()
{
String mesg;

 mesg = Device;
   IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 /////////////////////////////////////////////////////////////////////////////////// Subscribe to "mytopic/cmd" and update the outputs they point to
isyclient->subscribe(mesg + "/cmd", [](const String & payload) {
    Serial.println("fron outputncmd" + payload);
String mypayload = "";
 mypayload = payload;
StaticJsonDocument<1024> instatus;
  int pincount = 1;
  DeserializationError error = deserializeJson(instatus, payload);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  ///////////////////////////////////// analog out
     // Deserialize the JSON document
float mee;
pincount = 1; 
Serial.println(mypayload.substring(2,5) + "at start of output");
if (( isymqtt->analogoutcount != 0) && ( mypayload.substring(2,4) == "AO"))
     {
//           thevalue =  *analogoutval[pincount];
 // Serial.println(pincount);
           if (payload.substring(2,5) == "AO1")
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mee = instatus["AO1"]; 
             mee = mee*100;
             *isymqtt->analogoutval[1] = mee;
              Serial.println(String(*isymqtt->analogoutval[1]) + "here 1 from analod A1");
               }
           if ((payload.substring(2,5) == "AO2") && (isymqtt->analogoutcount >= 2))
              {
             mee = instatus["AO2"]; 
              Serial.println(String(mee) + "here 2 from analog AO2");
             *isymqtt->analogoutval[2] = (mee * 100);
               }
           if ((payload.substring(2,5) == "AO3") && (isymqtt->analogoutcount >= 3))
              {
             mee = instatus["AO3"]; 
             *isymqtt->analogoutval[3] = (mee * 100);
               }
           if ((payload.substring(2,5) == "AO4") && (isymqtt->analogoutcount >= 4))
              {
             mee = instatus["AO4"]; 
             *isymqtt->analogoutval[4] = (mee * 100);
               }
           if ((payload.substring(2,5) == "AO5") && (isymqtt->analogoutcount >= 5))
              {
             mee = instatus["AO5"]; 
             *isymqtt->analogoutval[5] = (mee * 100);
               }
             pincount++;

          
    pincount = 1; 
    }
 ///////////////////////////////////// analog out
     // Deserialize the JSON document
pincount = 1; 
//Serial.println(mypayload.substring(2,5));
if (( isymqtt->digitaloutcount != 0) && ( mypayload.substring(2,4) == "DO"))
     {
//           thevalue =  *analogoutval[pincount];
 Serial.println(payload.substring(2,5));
           if ((payload.substring(2,5) == "DO1") && (isymqtt->digitaloutcount >= 1))
              {
             mee = instatus["DO1"]; 
              Serial.println(String(mee) + " here 1 DO1");
             *isymqtt->digitaloutval[1] = mee;
               }
           if ((payload.substring(2,5) == "DO2") && (isymqtt->digitaloutcount >= 2))
              {
             mee = instatus["DO2"]; 
              Serial.println(String(mee) + "here 2 DO2");
             *isymqtt->digitaloutval[2] = mee;
               }
           if ((payload.substring(2,5) == "DO3") && (isymqtt->digitaloutcount >= 3))
              {
             mee = instatus["DO3"]; 
             *isymqtt->digitaloutval[3] = mee;
               }
           if ((payload.substring(2,5) == "DO4") && (isymqtt->digitaloutcount >= 4))
              {
             mee = instatus["DO4"]; 
             *isymqtt->digitaloutval[4] = mee;
               }
           if ((payload.substring(2,5) == "DO5") && (isymqtt->digitaloutcount >= 5))
              {
             mee = instatus["DO5"]; 
             *isymqtt->digitaloutval[5] = mee;
               }
    }

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
setupdone = 1;
}


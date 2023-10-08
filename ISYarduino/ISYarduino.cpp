 #include "ISYarduino.h"

String message;
String statmessage;
int setupdone = 0;

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

void isyMQTT::run(void)
{
serializeJson(doc, message);
  // Optional functionalities of EspMQTTClient
  //client.enableLastWillMessage( toCharArray(mesg) , "I am going offline");  // You can activate the retain flag by setting the third parameter to true

}

void isyMQTT::loop(void)
{
  isyclient->loop();
int thevalue;
String mesg;
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
 // Serial.println(pincount);
           if (thevalue != lastanaloginval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["AI" + String(analogcount)] = *analoginval[pincount];
 
              lastanaloginval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    pincount = 1; 
    }
  ///////////////////////////////////// analog out
  if ((analogoutcount != 0) && (setupdone == 1))
     {
      while (pincount <= analogoutcount)
          {
           thevalue =  *analogoutval[pincount];
 // Serial.println(pincount);
           if (thevalue != lastanalogoutval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["AO" + String(analogoutcount)] = *analogoutval[pincount];
 
              lastanalogoutval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    pincount = 1; 
    }
  ///////////////////////////////////// digital in
  if ((digitalincount != 0) && (setupdone == 1))
     {
      while (pincount <= digitalincount)
          {
           thevalue =  *digitalinval[pincount];
 // Serial.println(pincount);
           if (thevalue != lastdigitalinval[pincount])
              {
//           //    dataoutput = '{"AO' + String(pincount)': "' String(analoginval[pincount]'"}';
             mystatus["DI" + String(digitalincount)] = *digitalinval[pincount];
 
              lastdigitalinval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    pincount = 1; 
    }
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
             mystatus["DO" + String(digitaloutcount)] = *digitaloutval[pincount];
 
              lastdigitaloutval[pincount] =  thevalue;
              newdataflage = 1;  /// set flag to send new data
               }
             pincount++;

          }
    pincount = 1; 
    }
if (newdataflage == 1)
{
               Serial.println(thevalue);
               Serial.println(thevalue);
               Serial.println(thevalue);
               Serial.println(thevalue);
               Serial.println(thevalue);
newdataflage = 0;
}

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
setupdone = 1;
}

 
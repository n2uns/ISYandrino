// 1.0.0
/*           Sonoff 4ch pro pins
GPIO0	Push Button 1 (HIGH = off, LOW = on)
GPIO9	Push Button 2 (HIGH = off, LOW = on)
GPIO10	Push Button 3 (HIGH = off, LOW = on)
GPIO14	Push Button 4 (HIGH = off, LOW = on)
GPIO12	Relay 1 and its status LED
GPIO5	Relay 2 and its status LED
GPIO4	Relay 3 and its status LED
GPIO15	Relay 4 and its status LED
GPIO13	Blue LED (HIGH = off, LOW = on)
*/

#include "ISYarduino.h"
char devicename[] = "fourchpro";  //// needs to be the name of you give your device and has to match the name is the node server

//////////////////////////////////////////// creat the MQTT conection 
  EspMQTTClient client(
  "graffhouse",   // WIFI SSID
  "Kevin8386",    // WIFI Password
  "192.168.18.185",  // MQTT Broker server ip
  "admin",   // Can be omitted if not needed
  "kevin8386",   // Can be omitted if not needed
  devicename,     // 
  1884              // The MQTT port, default to 1883. this line can be omitted
);
isyMQTT thismqtt( &client);

unsigned long mytime;

const int pushb1 = 0;
const int pushb2 = 9;
const int pushb3 = 10;
const int pushb4 = 14;
const int prelay1 = 12;
const int prelay2 = 5;
const int prelay3 = 4;
const int prelay4 = 15;
const int pblueled = 13;

int but1; 
int but2;   
int but3;   
int but4;    
int relay1;    
int relay2;   
int relay3;
int relay4;




void setup()
{
Serial.begin(115200);

thismqtt.start(4,4,0,0);  //start the connection start(num of digital imputs, num of digital outputs, number of analog inputs, num of anilog outputs)

////// each io is declared type of io (variable int, discription to be displayed)
thismqtt.digitaloutput(&relay1,"relay no 1");
thismqtt.digitaloutput(&relay2,"relay no 2");
thismqtt.digitaloutput(&relay3,"relay no 3");
thismqtt.digitaloutput(&relay4,"relay no 4");
thismqtt.digitalinput(&but1,"push button 1");
thismqtt.digitalinput(&but2,"push button 2");
thismqtt.digitalinput(&but3,"push button 3");
thismqtt.digitalinput(&but4,"push button 4");
thismqtt.run(&thismqtt, devicename); //// builds discriptor of the node infomation

  pinMode (prelay1, OUTPUT);
  pinMode (prelay2, OUTPUT);
  pinMode (prelay3, OUTPUT);
  pinMode (prelay4, OUTPUT);
  pinMode (pushb1, INPUT);
  pinMode (pushb2, INPUT);
  pinMode (pushb3, INPUT);
  pinMode (pushb4, INPUT);

}


void loop()
{


 if ( digitalRead(pushb1) == LOW)  // read in button low is pressed
 {relay1 = 100; // set ISY to display on
 digitalWrite(prelay1, HIGH); // turn on the relay
 but1 = 100; // show button on
  } else{
  relay1 = 0; // set ISY to display off
 digitalWrite(prelay1, LOW); // turn off the relay
 but1 = 0; // show button off  
  }
 
 if ( digitalRead(pushb2) == LOW)  // read in button low is pressed
 {relay2 = 100; // set ISY to display on
 digitalWrite(prelay2, HIGH); // turn on the relay
 but2 = 100; // show button on
  } else{
  relay2 = 0; // set ISY to display off
 digitalWrite(prelay2, LOW); // turn off the relay
 but2 = 0; // show button off  
  }
 
 if ( digitalRead(pushb3) == LOW)  // read in button low is pressed
 {relay3 = 100; // set ISY to display on
 digitalWrite(prelay3, HIGH); // turn on the relay
 but3 = 100; // show button on
  } else{
  relay3 = 0; // set ISY to display off
 digitalWrite(prelay3, LOW); // turn off the relay
 but3 = 0; // show button off  
  }
 
 if ( digitalRead(pushb4) == LOW)  // read in button low is pressed
 {relay4 = 100; // set ISY to display on
 digitalWrite(prelay4, HIGH); // turn on the relay
 but4 = 100; // show button on
  } else{
  relay4 = 0; // set ISY to display off
 digitalWrite(prelay4, LOW); // turn off the relay
 but4 = 0; // show button off  
  }



  thismqtt.loop();

}


// 1.0.0

#include "ISYarduino.h"
char devicename[] = "shed";  //// needs to be the name of you give your device and has to match the name is the node server

//////////////////////////////////////////// creat the MQTT conection 
  EspMQTTClient client(
  "graffhouse",   // WIFI SSID
  "Kevin8386",    // WIFI Password
  "192.168.18.185",  // MQTT Broker server ip
  "admin",   // Can be omitted if not needed
  "kevin8386",   // Can be omitted if not needed
  devicename,     // Client name that uniquely identify your device
  1884              // The MQTT port, default to 1883. this line can be omitted
);
isyMQTT thismqtt( &client);

unsigned long mytime;

const int Analogin = 36;
const int Digout = 16;
const int Bultinled = 2;
int me;

int battin;
int acout;
int ledout;




void setup()
{
Serial.begin(115200);

thismqtt.start(1,1,0,2);  //start the connection start(num of digital imputs, num of digital outputs, number of analog inputs, num of anilog outputs)

////// each io is declared type of io (variable int, discription to be displayed)
thismqtt.analoginput(&battin,"battery voltage");
thismqtt.digitaloutput(&acout,"main 120vac power to shed");
thismqtt.digitaloutput(&ledout,"on board led");
thismqtt.run(&thismqtt, devicename); //// builds discriptor of the node infomation

  pinMode (Digout, OUTPUT);
  pinMode (Bultinled, OUTPUT);
ledout = 100;
digitalWrite(Bultinled, HIGH);
mytime =  millis();
mytime = mytime + 5000;

}


void loop()
{


  // Execute delayed toggle of built  in led without slowing down loop
if (mytime <= millis())    {
//delay(5000);
    if (me == 0)
        {
        ledout = 0;
        mytime = millis();
        mytime = mytime + 5000;
        me = 100;
        }
    else {                                     // was here
        ledout = 100;
        mytime = millis();
        mytime = mytime + 5000;
        me = 0;
        }

}
if (ledout == 0) {     
     digitalWrite(Bultinled, LOW);
     }
if (ledout == 100) {     
     digitalWrite(Bultinled, HIGH);
     }

  thismqtt.loop();

}


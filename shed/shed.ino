// 1.0.0

#include "ISYarduino.h"
char devicename[] = "shed";  //// needs to be the name of you give your device and has to match the name is the node server

//////////////////////////////////////////// creat the MQTT conection 
  EspMQTTClient client(
  "graffhouse",   // WIFI SSID
  "Kevin8386",    // WIFI Password
  "192.168.18.161",  // MQTT Broker server ip
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
int batv[11];
int count = 0;

int battin;
int acout;
int ledout;
int setout;
int pass = 0;




void setup()
{
Serial.begin(115200);

thismqtt.start(1,1,0,2);  //start the connection start(num of digital imputs, num of digital outputs, number of analog inputs, num of anilog outputs)

////// each io is declared type of io (variable int, discription to be displayed)
thismqtt.analoginput(&battin,"battery voltage");
thismqtt.analogoutput(&setout,"AC power trip point");
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
if (mytime <= millis())    
  {
//delay this part of the loop runs every 3 sec
  count++;
  pass++;
  batv[count] = analogRead(Analogin);
  if (count == 10)
  {
  count = 0;
  battin = ((batv[1] + batv[2] + batv[3] + batv[4] + batv[5] + batv[6] + batv[7] + batv[8] + batv[9] + batv[10])/10 ) / 1.427;  //  get average of 10 readings and devide by trim amount
  }
    if ((me == 0) && (pass == 9))
        {
        ledout = 0;         ////////////    this just toggles the on board led
        me = 100;
        }
    if (pass == 10) {                                     // was here
        ledout = 100;
        me = 0;
        pass = 0;
        }
 
  mytime = millis();
  mytime = mytime + 1000;
  }

if (setout >= battin )
{
      digitalWrite(Digout, LOW); 
      acout = 0;
}
else {
      digitalWrite(Digout, HIGH); 
      acout = 100 ;
}
if (ledout == 0) {     
     digitalWrite(Bultinled, LOW);
     }
if (ledout == 100) {     
     digitalWrite(Bultinled, HIGH);
     }

  thismqtt.loop();

}


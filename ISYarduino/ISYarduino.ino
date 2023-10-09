// 1.0.0

#include "ISYarduino.h"
char devicename[] = "mydevice";  //// needs to be the name of you give your device and has to match the name is the node server

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


const int Analogin = 36;
const int DigIn = 23;
const int Digout = 16;
const int Bultinled = 2;
int me;

int testanalogin;
int lightout;
int battcharge;
int lightsw;
int a2;




void setup()
{
Serial.begin(115200);

thismqtt.start(1,1,0,2);  //start the connection start(num of digital imputs, num of digital outputs, number of analog inputs, num of anilog outputs)

////// each io is declared type of io (variable int, discription to be displayed)
thismqtt.analoginput(&testanalogin,"battery voltage");
thismqtt.analogoutput(&lightout,"my AO1");
thismqtt.analogoutput(&a2,"my AO2");
thismqtt.digitaloutput(&battcharge,"my DO1");
thismqtt.digitaloutput(&lightsw,"my DO2");
thismqtt.run(&thismqtt, devicename); //// builds discriptor of the node infomation

  pinMode (Digout, OUTPUT);
  pinMode (DigIn, INPUT);
testanalogin = 288;
 

}


void loop()
{
 String mesg;
 //mesg = Device;
//   client.loop();
  me = me + 1;
  // Execute delayed toggle of analog in without slowing down loop
if ((me >= 120000) && (me <= 240000))   {
testanalogin = 156;
}
if (me >= 240000)   {
testanalogin = 586;
me = 0;
}
//              Serial.println(String(battcharge) + "batt");
//              Serial.println(String(lightsw) + "light");
  thismqtt.loop();

}


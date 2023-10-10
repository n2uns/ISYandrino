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
thismqtt.analoginput(&testanalogin,"battery voltage");  // displays int / 100.00  So 5839 will display 58.39
thismqtt.analogoutput(&lightout,"my AO1");   // displays int / 100.00  So 5839 will display 58.39
thismqtt.analogoutput(&a2,"my AO2");   // displays int / 100.00  So 5839 will display 58.39
thismqtt.digitaloutput(&battcharge,"my DO1");  // int = 0 will display off int = 100 will display on
thismqtt.digitaloutput(&lightsw,"my DO2");  // int = 0 will display off int = 100 will display on
thismqtt.run(&thismqtt, devicename); //// builds discriptor of the node infomation

  pinMode (Digout, OUTPUT);
  pinMode (DigIn, INPUT);
testanalogin = 288; // displays 2.88
 

}

// keep the loop running as fast as you can or it will slow down the refress rate of the controller
void loop()
{
 String mesg;
 //mesg = Device;
//   client.loop();
  me = me + 1;
  // Execute delayed toggle of analog in without slowing down loop
if ((me >= 120000) && (me <= 240000))   {
testanalogin = 156; // displays 1.56
}
if (me >= 240000)   {
testanalogin = 586; // displays 5.86
me = 0;
}
//              Serial.println(String(battcharge) + "batt");
//              Serial.println(String(lightsw) + "light");
  thismqtt.loop();  // checks if any vaules changed and sends them if so and prossess any incoming changes from the controler 

}




#include "ISYarduino.h"

//////////////////////////////////////////// creat the MQTT conection 
  EspMQTTClient client(
  "graffhouse",   // WIFI SSID
  "Kevin8386",    // WIFI Password
  "192.168.18.185",  // MQTT Broker server ip
  "admin",   // Can be omitted if not needed
  "kevin8386",   // Can be omitted if not needed
  "mydevice",     // Client name that uniquely identify your device
  1884              // The MQTT port, default to 1883. this line can be omitted
);

isyMQTT thismqtt( &client);


const int Analogin = 36;
const int DigIn = 23;
const int Digout = 16;
const int Bultinled = 2;
int me;

int tst;
int lightout;
int battcharge;
int lightsw;





void setup()
{
Serial.begin(115200);

thismqtt.start(1,1,0,2);  //start the connection start(num of digital imputs, num of digital outputs, number of analog inputs, num of anilog outputs)

////// each io is declared type of io (variable int, discription to be displayed)
thismqtt.analoginput(&tst,"battery voltage");
thismqtt.analogoutput(&lightout,"Light Brightness");
thismqtt.digitaloutput(&battcharge,"Battery charger sw");
thismqtt.digitaloutput(&lightsw,"Light sw");
thismqtt.run(); //// builds discriptor of the node infomation

  pinMode (Digout, OUTPUT);
  pinMode (DigIn, INPUT);
tst = 288;
 

}


void loop()
{
 String mesg;
 //mesg = Device;
//   client.loop();
  me = me + 1;
  // Execute delayed instructions
if (me >= 120000)   {
me=0;
tst = 156;
 //client.publish(mesg + "/cmd", "my cmd is " + String( digitalRead( Digout )));
// Publish a message to "mytopic/Discovery"

}
//  Serial.println(me);
  thismqtt.loop();

}


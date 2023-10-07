#include <ArduinoJson.h>
#include "EspMQTTClient.h"


// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient



class isyMQTT {
 
 public:
      isyMQTT(EspMQTTClient* myclient);

void start(int analogin, int analogout, int digitalin, int digitalout);
void analoginput( int &var1 , char displayname1[]);
void analogoutput( int &analogoutvar1 , char displayname1[]);
void digitalinput( int &digitalinvar1 , char displayname1[]);
void digitaloutput( int &digitaloutvar1 , char displayname1[]);
void run(void);
void loop(void);

int pincount;
int totalpins;
int analogcount;
int analoginval[5];

  private:
StaticJsonDocument<1024> doc;
EspMQTTClient myclient;
int *var1;
int analogoutcount;
int analogoutval[5];
int *analogoutvar1;

int digitalincount;
int digitalinval[5];
int *digitalinvar1;
int digitaloutcount;
int digitaloutval[5];
int *digitaloutvar1;


};
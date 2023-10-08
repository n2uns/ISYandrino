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
void run(void);
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
int analogoutcount;
int *analogoutval[6];
int *analogoutvar1;

int digitalincount;
int *digitalinval[6];
int *digitalinvar1;
int digitaloutcount;
int *digitaloutval[6];
int *digitaloutvar1;

int lastanaloginval[5];
int lastanalogoutval[5];
int lastdigitalinval[5];
int lastdigitaloutval[5];


};
/*
 Example usage for InfluxDB library by Richard Lyon.
 */

// InfluxDB credentials
#define USERNAME "kingswood_admin"
#define PASSWORD "Wbtc0rar"

#include "InfluxDB.h"
InfluxDB idb = InfluxDB(USERNAME, PASSWORD);

int photoresistor = A0;
int power = A5;
long int timestamp;
double analogvalue;

void setup() {
  Serial.begin(9600);
  pinMode(photoresistor,INPUT);
  pinMode(power,OUTPUT);
  digitalWrite(power,HIGH);

  // initialise InfluxDB
  idb.setDatabase("test");        // defaults to 'sensordata'
  idb.setDeviceName("elmon");     // defaults to "particle"
  idb.setDebug(true);             // defaults to false
}

void loop() {
  timestamp = Time.now();
  analogvalue = analogRead(photoresistor) * 1.0;
  idb.add("photoresistor", analogvalue);
  idb.add("dummy", 3.1415);
  if (idb.sendAll()) {            // call this to send points to InfluxDB
    Serial.println("InfluxDB updated");
  }
  delay(1000);
}
